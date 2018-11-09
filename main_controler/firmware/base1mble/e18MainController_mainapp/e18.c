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
	wiced_rtos_init_queue(&pumpRequestQueueHandle, "pumpRequestQueue", sizeof(pumps_speed_request_t), QUEUE_SIZE); /* Setup the queue for pump run requests  */
	wiced_rtos_init_queue(&pumpCommandQueueHandle, "blinkQueue", sizeof(pumps_command_request_t), QUEUE_SIZE); /* Setup the queue for pump commands */

	//start the various threads
	wiced_rtos_create_thread(&gameThreadHandle, GAME_THREAD_PRIORITY, "gameThread", gameStateMachine, GAME_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&awsThreadHandle, AWS_THREAD_PRIORITY, "awsThread", awsThread, AWS_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&levelThreadHandle, LEVEL_THREAD_PRIORITY, "levelThread", levelThread, LEVEL_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&pumpThreadHandle, PUMP_THREAD_PRIORITY, "pumpThread", pumpsThread, PUMP_STACK_SIZE, NULL);

	startBle();

	//needs to happen after pump thread is inited for pumps to work
#ifdef TEST_HARDWARE_ON_STARTUP
	Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
	Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
	wiced_rtos_delay_milliseconds(500);

	pumpsSendEnable();
	pumpsSendValues(100,100);

	wiced_rtos_delay_milliseconds(750);
	Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_OFF);	//turn on arm switch LED
	Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_OFF);	//turn on arm switch LED
	pumpsSendDisable();

#endif

	WPRINT_APP_INFO(("Initializing stuff done\n"));

	//this is the default application thread, using it to handle capsense and user interface (switches, LEDs)
	while(1)
	{
		//read and handle the arm/abort switch
		if(Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN) == SWITCH_ON)
		{
			pumpsSendEnable();

			Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
			if(getGameState() == GAME_ABORT)
				gameStateRequest = REQUEST_RESET;
		}
		else
		{
			pumpsStopAll();                                     //set the pump PWMs to zero
			pumpsSendDisable();
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
