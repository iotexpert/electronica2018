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

/** @file
 *
 * Concurrent APSTA Application
 *
 * This application snippet demonstrates how to use
 * the WICED Wi-Fi client and softAP interfaces at the same time.
 *
 * Features demonstrated
 *  - Wi-Fi client mode (to send a regular ICMP ping to an AP)
 *  - Wi-Fi softAP mode (to enable Wi-Fi clients to connect to the WICED webserver)
 *
 * To demonstrate the app, work through the following steps.
 *  1. Modify the CLIENT_AP_SSID/CLIENT_AP_PASSPHRASE Wi-Fi credentials
 *     in the wifi_config_dct.h header file to match your Wi-Fi access point
 *  2. Modify the SOFT_AP_SSID/SOFT_AP_PASSPHRASE Wi-Fi credentials
 *     as desired
 *  3. Plug the WICED eval board into your computer
 *  4. Open a terminal application and connect to the WICED eval board
 *  5. Build and download the application (to the WICED board)
 *
 * After the download completes, the terminal displays WICED startup
 * information and then :
 *  - Joins a Wi-Fi network and pings the gateway. Ping results are
 *    printed to the UART and appear on the terminal
 *  - Starts a softAP and a webserver on the AP interface
 *
 * To connect a Wi-Fi client (eg. computer) to the softAP webserver:
 *  - Connect your computer to the softAP SSID configured in wifi_config_dct.h
 *  - Open a web browser
 *  - Enter wiced.com as the URL; a simple web page appears
 *    (or alternately, enter 192.168.0.1 as the URL, this is the
 *     IP address of the softAP interface)
 *
 * TROUBLESHOOTING
 *   If you are having difficulty connecting the web browser to the
 *   WICED softAP webserver, try the following:
 *   1. Disconnect other network interfaces from the computer (eg. wired ethernet)
 *   2. Check that your computer received a valid IP address eg. 192.168.0.2
 *   3. Try clearing the web browser cache and try connecting again
 *
 */

#include "wiced.h"
#include "cy_pdl.h"
#include "cycfg.h"
#include "sound.h"
#include "pumps.h"
#include "cycfg_pins.h"
#include "game.h"
#include "aws.h"
#include "bt.h"
#include "liquidlevel.h"
#include "leduart.h"
#include "game_console.h"

/******************************************************
 *               Variable Definitions
 ******************************************************/
static wiced_thread_t gameThreadHandle;
static wiced_thread_t awsThreadHandle;
static wiced_thread_t btThreadHandle;
static wiced_thread_t soundThreadHandle;
//static wiced_thread_t consoleThreadHandle;

//globals for game
uint8_t leftLevel;
uint8_t rightLevel;
uint8_t leftPumpRequest = 0;
uint8_t rightPumpRequest = 0;
uint32_t systicks = 0;		    //system ticks incremented in startup thread


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

//#define CONSOLE_THREAD_PRIORITY	9
// #define AWS_THREAD_PRIORITY		8
// #define GAME_THREAD_PRIORITY	10
// #define BT_THREAD_PRIORITY		11
// #define SOUND_THREAD_PRIORITY	12

#define AWS_THREAD_PRIORITY		4
#define GAME_THREAD_PRIORITY	7
#define BT_THREAD_PRIORITY		7
#define SOUND_THREAD_PRIORITY	8

#define THREAD_STACK_SIZE 6144
#define GAME_STACK_SIZE 4096
#define SOUND_THREAD_STACK_SIZE 512

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

    //init_cycfg_all();             don't do this!!!

    initAudioHW();
    //initConsoleUART();        //was using this in the bare metal version, but WICED handles this UART
    ledUARTinit();

    /* enable interrupts */
    __enable_irq();

    initLevelSense();       //initialize capsense and interrupts
    initPumpHW();           //initialize pump PWMs
    initGameConsole();      //initialize wiced sdk based game console

	wiced_rtos_create_thread(&gameThreadHandle, GAME_THREAD_PRIORITY, "gameThread", gameStateMachine, GAME_STACK_SIZE, NULL);
    wiced_rtos_create_thread(&awsThreadHandle, AWS_THREAD_PRIORITY, "awsThread", awsThread, THREAD_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&btThreadHandle, BT_THREAD_PRIORITY, "btThread", btThread, THREAD_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&soundThreadHandle, SOUND_THREAD_PRIORITY, "soundThread", soundThread, SOUND_THREAD_STACK_SIZE, NULL);
	//wiced_rtos_create_thread(&consoleThreadHandle, CONSOLE_THREAD_PRIORITY, "consoleThread", consoleThread, THREAD_STACK_SIZE, NULL);    

	//this is the default application thread, using it to handle capsense and user interface (switches, LEDs)
    while(1)
    {
        //read and handle the arm/abort switch
        if(Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN) == SWITCH_ON)
        {
            Cy_GPIO_Write(pumpEnable_PORT, pumpEnable_PIN, 1);	//enable pump h-bridge            
            Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
            GAME_STATE_T currentState = getGameState();
            if(currentState == GAME_ABORT || currentState == GAME_WIN)
            {
                gameStateRequest = REQUEST_RESET;
            }
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

        handleLevelSense();                 //perform the low level capsense read
        determineLevels();                  //calculate the water levels
        handleHeartBeatLED();               //handle the heartbeat LED
        handleRunLED();                      //handle the game run status LED
		pumpDecay();                        //during game play the pump speed decays
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
