/*
 * Copyright 2018, Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All Rights Reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software"), is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */


#include "wiced.h"
#include "cy_pdl.h"
#include "cycfg.h"
#include "sound.h"
#include "pumps.h"
#include "cycfg_pins.h"
#include "game.h"
#include "aws.h"
#include "liquidlevel.h"
#include "leduart.h"
#include "game_console.h"
#include "ble_app.h"


/******************************************************
 *               Variable Definitions
 ******************************************************/
static wiced_thread_t gameThreadHandle;
static wiced_thread_t awsThreadHandle;
static wiced_thread_t pumpThreadHandle;
static wiced_thread_t levelThreadHandle;

wiced_queue_t pumpRequestQueueHandle;
wiced_queue_t pumpCommandQueueHandle;

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
#define HEARTBEAT_LED_OFF_COUNTS    22
#define HEARTBEAT_LED_ON_COUNTS     1
#define GAME_LED_OFF_COUNTS         8
#define GAME_LED_ON_COUNTS          12

#define AWS_THREAD_PRIORITY		4
#define LEVEL_THREAD_PRIORITY   6
#define PUMP_THREAD_PRIORITY    6
#define GAME_THREAD_PRIORITY	7

#define AWS_STACK_SIZE 6144
#define GAME_STACK_SIZE 4096
#define LEVEL_STACK_SIZE 1024
#define PUMP_STACK_SIZE 1024

/* The queue messages will be 4 bytes each (a 32 bit integer) */
#define MESSAGE_SIZE		(4)
#define QUEUE_SIZE			(10)

#define TEST_HARDWARE_ON_STARTUP        //turn on switch LEDs and briefly kick pumps on start-up

/******************************************************
 *                   Enumerations
 ******************************************************/


/******************************************************
 *                 Type Definitions
 ******************************************************/
typedef enum{
	ONBOARD_LED_ON,
	ONBOARD_LED_OFF
}ONBOARD_LED_ONOFF_T;

typedef enum{
	SWITCH_ON,
	SWITCH_OFF
}SWITCH_INPUT_T;

typedef enum{
	EXTERNAL_LED_OFF,
	EXTERNAL_LED_ON
}EXTERNAL_LED_ONOFF_T;

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Static Function Declarations
 ******************************************************/


/******************************************************
 *               Variable Definitions
 ******************************************************/

/******************************************************
 *               Local Function Prototypes
 ******************************************************/
void handleRunLED(void);
void handleHeartBeatLED(void);

/******************************************************
 *               Function Definitions
 ******************************************************/
void application_start(void)
{
	static SWITCH_INPUT_T previousStartSwitch = SWITCH_OFF;

	/* Initialise the device */
	wiced_init();


	WPRINT_APP_INFO(("Starting project\n"));
	wiced_result_t result;

	do
	{
		result = wiced_network_up( WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
		wiced_rtos_delay_milliseconds(200);
	} while(result != WICED_SUCCESS);


	initGameConsole();
	ledUARTinit();          //this uart is handled by interrupt, no thread to init it in
	initAudioHW();          //audio is handled by DMA and PWM, no thread to initialize those

	/* enable interrupts */
	__enable_irq();

	//initialize the pump queues
	wiced_rtos_init_queue(&pumpRequestQueueHandle, "pumpRequestQueue", MESSAGE_SIZE, QUEUE_SIZE); /* Setup the queue for pump run requests  */
	wiced_rtos_init_queue(&pumpCommandQueueHandle, "blinkQueue", MESSAGE_SIZE, QUEUE_SIZE); /* Setup the queue for pump commands */

	//start the various threads
	wiced_rtos_create_thread(&gameThreadHandle, GAME_THREAD_PRIORITY, "gameThread", gameStateMachine, GAME_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&awsThreadHandle, AWS_THREAD_PRIORITY, "awsThread", awsThread, AWS_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&levelThreadHandle, LEVEL_THREAD_PRIORITY, "levelThread", levelThread, LEVEL_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&pumpThreadHandle, PUMP_THREAD_PRIORITY, "pumpThread", pumpThread, PUMP_STACK_SIZE, NULL);

	startBle();

	//needs to happen after pump thread is inited for pumps to work
#ifdef TEST_HARDWARE_ON_STARTUP
	Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
	Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
	wiced_rtos_delay_milliseconds(500);
	setPumpSpeed(LEFT_PUMP, 100);                       //low level pump test
	setPumpSpeed(RIGHT_PUMP, 100);
	wiced_rtos_delay_milliseconds(750);
	Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_OFF);	//turn on arm switch LED
	Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_OFF);	//turn on arm switch LED
	setPumpSpeed(LEFT_PUMP, 0);
	setPumpSpeed(RIGHT_PUMP, 0);
#endif

	WPRINT_APP_INFO(("Initializing stuff done\n"));

	//this is the default application thread, using it to handle capsense and user interface (switches, LEDs)
	while(1)
	{
		//read and handle the arm/abort switch
		if(Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN) == SWITCH_ON)
		{
			Cy_GPIO_Write(pumpEnable_PORT, pumpEnable_PIN, 1);	//enable pump h-bridge
			Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
			if(getGameState() == GAME_ABORT)
				gameStateRequest = REQUEST_RESET;
		}
		else
		{
			Cy_GPIO_Write(pumpEnable_PORT, pumpEnable_PIN, 0);	//disable pump h-bridge, and...
			stopAllPumps();                                     //set the pump PWMs to zero
			Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_OFF);	//turn off arm switch LED
			gameStateRequest = REQUEST_ABORT;                   //"request" game abort
		}

		//read and handle the start/pause switch
		if(previousStartSwitch == SWITCH_OFF)
		{
			if(Cy_GPIO_Read(startButton_PORT, startButton_PIN) == SWITCH_ON)
			{
				previousStartSwitch = SWITCH_ON;
				startButtonPress = START_PRESS_TRUE;
			}
		}
		else
		{
			if(Cy_GPIO_Read(startButton_PORT, startButton_PIN) == SWITCH_OFF)
			{
				previousStartSwitch = SWITCH_OFF;
			}
		}

		handleHeartBeatLED();               //handle the heartbeat LED
		handleRunLED();                      //handle the game run status LED
		wiced_rtos_delay_milliseconds(50);  //sleep for 50ms
	}
}


//moved these to their own functions to clarify application default thread loop
void handleRunLED(void)
{    
	static uint8_t gameLedTicks = 0;
	GAME_STATE_T currentGameState;

	currentGameState = getGameState();

	switch(currentGameState)
	{
	case GAME_START:
	case GAME_RUNNING:
		Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_ON);
		gameLedTicks = 0;
		break;

	case GAME_PAUSE:
		if(Cy_GPIO_ReadOut(startLED_PORT, startLED_PIN) == EXTERNAL_LED_OFF)
		{
			if(gameLedTicks == GAME_LED_OFF_COUNTS)
			{
				gameLedTicks = 0;
				Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_ON);
			}
		}
		else
		{
			if(gameLedTicks == GAME_LED_ON_COUNTS)
			{
				gameLedTicks = 0;
				Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_OFF);
			}
		}
		gameLedTicks++;
		break;

	default:
		Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_OFF);
		break;
	}

}

void handleHeartBeatLED(void)
{
	static uint16_t heartBeatTicks = 0;

	if(Cy_GPIO_ReadOut(GREEN_LED_PORT, GREEN_LED_PIN) == ONBOARD_LED_OFF)
	{
		if(heartBeatTicks == HEARTBEAT_LED_OFF_COUNTS)
		{
			heartBeatTicks = 0;
			Cy_GPIO_Write(GREEN_LED_PORT, GREEN_LED_PIN, ONBOARD_LED_ON);
		}
	}
	else
	{
		if(heartBeatTicks == HEARTBEAT_LED_ON_COUNTS)
		{
			heartBeatTicks = 0;
			Cy_GPIO_Write(GREEN_LED_PORT, GREEN_LED_PIN, ONBOARD_LED_OFF);
		}
	}
	heartBeatTicks++;
}
