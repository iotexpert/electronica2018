/*
 * game.c
 *
 *  Created on: Sep 13, 2018
 *      Author: kmwh
 */


#include "wiced.h"
#include "game.h"
#include "sound.h"
#include "aws.h"
#include "pumps.h"
#include "game_console.h"
#include "leduart.h"
#include "resources.h"
#include "liquidlevel.h"


//game state machine defines
#define GAME_MACHINE_DELAY	125		//time in milliseconds of delay for game machine thread
#define GAME_WIN_LEVEL	70			//percent water level for a win to be triggered

//#define GAME_HARDWARE_TEST			//define this to start the pumps on game start for hardware test
//#define IDLE_SOUND_TEST_MODE		//repeatedly plays sound in idle mode


//variables
static volatile GAME_STATE_T gameState = GAME_INIT;			//the game state

START_PRESS_T startButtonPress = START_PRESS_NONE;			//used by gui handler to indicate a start button press

GAME_STATE_REQUEST_T gameStateRequest = REQUEST_NONE;		//used by external events to request a game state change


//function prototypes
//making game states their own functions to clarify game state machine thread
GAME_STATE_T gameStateInit(void);			//has its own state machine to do start-up LED check and print help info
GAME_STATE_T gameStateIdle(void);
GAME_STATE_T gameStateRunning(void);
GAME_STATE_T gameStateWin(void);

//code
//game state machine thread
void gameStateMachine(wiced_thread_arg_t arg)
{
	static volatile GAME_STATE_T previousState = GAME_UNKNOWN;
	GAME_STATE_T subState;
	uint32_t pumpCommand;

	//game state machine thread loop
	while(1)
	{
		//check to see if a state change has occurred, if so print to serial port
		if(previousState != gameState)
		{
			uint8_t stateString[40];
			getGameStateString(stateString);
			WPRINT_APP_INFO(("Changing to state: %s\n", stateString));
			previousState = gameState;
		}

		//and run the game state machine
		switch(gameState)
		{
			case GAME_INIT:
				if(gameStateInit() == GAME_IDLE)
				{
					gameState = GAME_IDLE;
				}
				break;

			case GAME_IDLE:
				if(gameStateIdle() == GAME_START)
				{
					gameState = GAME_START;
				}
				break;

			case GAME_START:
				if(getSoundState() == SOUND_IDLE) gameState = GAME_RUNNING;

				if(gameStateRequest == REQUEST_ABORT)
				{
					gameState = GAME_ABORT;
				}
				break;

			case GAME_RUNNING:
				subState = gameStateRunning();
				switch(subState)
				{
					case GAME_RUNNING:
						break;

					case GAME_PAUSE:					
						gameState = GAME_PAUSE;
						break;

					case GAME_WIN:
						gameState = GAME_WIN;
						break;
					
					case GAME_ABORT:
						gameState = GAME_ABORT;
						break;						
				}
				break;

			case GAME_PAUSE:
				if(startButtonPress || gameStateRequest == REQUEST_RESUME)
				{
					gameState = GAME_RUNNING;
					startButtonPress = START_PRESS_NONE;
					pumpCommand = (uint32_t) PUMPS_ENABLED;
					wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/
				}

				if(gameStateRequest == REQUEST_ABORT)
				{
					pumpCommand = (uint32_t) PUMPS_DISABLED;
					wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/
					gameState = GAME_ABORT;
				}
				break;

			case GAME_WIN:
				if(gameStateWin() == GAME_IDLE)
				{
					gameState = GAME_IDLE;
				}
				break;

			default:
			case GAME_UNKNOWN:
			case GAME_ABORT:
				leftColor.blue = 0x00;
				leftColor.red = 0x00;
				leftColor.green = 0x00;
				rightColor.blue = 0x00;
				rightColor.red = 0x00;
				rightColor.green = 0x00;
				ledUARTsendColorValues(0, 0);			//turn off LED strips					

				if(gameStateRequest == REQUEST_RESET)	//wait for a reset
				{
					gameState = GAME_IDLE;
					gameStateRequest = REQUEST_NONE;
				}				
				break;
		}
		gameStateRequest = REQUEST_NONE;
		wiced_rtos_delay_milliseconds(GAME_MACHINE_DELAY);
	}
}

GAME_STATE_T gameStateInit(void)
{
	static uint16_t initTicks = 0;

	uint32_t pumpCommand;	
	GAME_STATE_T returnValue = GAME_INIT;

	switch(initTicks)
	{
		case 0:
			pumpCommand = (uint32_t) PUMPS_DISABLED;
			wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/
			consolePrintWelcome();
			leftColor.blue = 0xFF;
			leftColor.red = 0xFF;
			leftColor.green = 0x00;
			rightColor.blue = 0xFF;
			rightColor.red = 0x00;
			rightColor.green = 0xFF;
			ledUARTsendColorValues(50, 50);			//set LED strips
			break;
		
		case 4:
			leftColor.blue = 0xFF;
			leftColor.red = 0xFF;
			leftColor.green = 0x00;
			rightColor.blue = 0xFF;
			rightColor.red = 0x00;
			rightColor.green = 0xFF;
			ledUARTsendColorValues(70, 70);			//set LED strips
			break;

		case 8:
			consolePrintStatus();
			leftColor.blue = 0xFF;
			leftColor.red = 0xFF;
			leftColor.green = 0x00;
			rightColor.blue = 0xFF;
			rightColor.red = 0x00;
			rightColor.green = 0xFF;
			ledUARTsendColorValues(85, 85);			//set LED strips
			break;

		case 10:
			leftColor.blue = 0xFF;
			leftColor.red = 0xFF;
			leftColor.green = 0x00;
			rightColor.blue = 0xFF;
			rightColor.red = 0x00;
			rightColor.green = 0xFF;
			ledUARTsendColorValues(100, 100);			//set LED strips
			break;	

		case 20:
			consolePrintHelp();
			leftColor.blue = 0x00;
			leftColor.red = 0x00;
			leftColor.green = 0x00;
			rightColor.blue = 0x00;
			rightColor.red = 0x00;
			rightColor.green = 0x00;
			ledUARTsendColorValues(0, 0);			//set LED strips
			initTicks = 0;
			returnValue = GAME_IDLE;
			break;

		default:
			break;
	}

	initTicks++;
	return returnValue;
}

GAME_STATE_T gameStateIdle(void)
{
	static uint16_t idleTicks = 0;
	uint32_t pumpCommand;

	GAME_STATE_T returnValue = GAME_IDLE;

	leftColor.blue = 0x00;
	leftColor.red = 0x00;
	leftColor.green = 0x00;
	rightColor.blue = 0x00;
	rightColor.red = 0x00;
	rightColor.green = 0x00;
	ledUARTsendColorValues(0, 0);			//set LED strips

	idleTicks++;
	if(idleTicks == 60)
	{
		idleTicks = 0;
		//various debugging tests
		//WPRINT_APP_INFO(("Still alive\n"));
		//reportLevels();
		//reportRawRightLevels();
		//reportRawLeftLevels();
		//reportRawLevels();

		//sound test
		#ifdef IDLE_SOUND_TEST_MODE
		if(getSoundState() == SOUND_IDLE)
		{
			static uint8_t which = 0;
			if(which == 0)
			{
				playSound(resources_fight_wav_data);
				which = 1;
			}
			else
			{
				playSound(resources_winner_wav_data);
				which = 0;
			}

		}
		#endif

	}

	
	if(startButtonPress || gameStateRequest == REQUEST_START)
	{
		playSound(resources_fight_wav_data);
		startButtonPress = START_PRESS_NONE;
		pumpCommand = (uint32_t) PUMPS_ENABLED;
		wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/
		returnValue = GAME_START;
		idleTicks = 0;
	}
	
	return returnValue;
}


//this function handles the game running state
GAME_STATE_T gameStateRunning(void)
{
	GAME_STATE_T returnValue = GAME_RUNNING;
	uint32_t pumpCommand;

	leftColor.blue = 0xFF;
	leftColor.red = 0x00;
	leftColor.green = 0x00;
	rightColor.blue = 0x00;
	rightColor.red = 0x00;
	rightColor.green = 0xFF;
	ledUARTsendColorValues(leftLevel, rightLevel);			//set LED strips

	if(startButtonPress || gameStateRequest == REQUEST_PAUSE)
	{
		pumpCommand = (uint32_t) PUMPS_DISABLED;
		wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/
		startButtonPress = START_PRESS_NONE;
		returnValue = GAME_PAUSE;
	}

	if(leftLevel > GAME_WIN_LEVEL || rightLevel > GAME_WIN_LEVEL)
	{
		pumpCommand = (uint32_t) PUMPS_DISABLED;
		wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/
		returnValue = GAME_WIN;
	}

	if(gameStateRequest == REQUEST_ABORT)
	{
		pumpCommand = (uint32_t) PUMPS_DISABLED;
		wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/
		returnValue = GAME_ABORT;					
	}

	return returnValue;
}

//this function handles the game win state
GAME_STATE_T gameStateWin(void)
{
	static uint16_t winTicks = 0;
	GAME_STATE_T returnValue = GAME_WIN;
	static uint8_t leftLED, rightLED;

	if(winTicks == 0)
	{
		consolePrintWin();
		playSound(resources_winner_wav_data);
		if(leftLevel > rightLevel)
		{
			leftColor.blue = 0xFF;
			leftColor.red = 0x00;
			leftColor.green = 0x00;
			rightColor.blue = 0x00;
			rightColor.red = 0x00;
			rightColor.green = 0x00;
			leftLED = 144;
			rightLED = 0;
		}
		else
		{
			leftColor.blue = 0x00;
			leftColor.red = 0x00;
			leftColor.green = 0x00;
			rightColor.blue = 0x00;
			rightColor.red = 0x00;
			rightColor.green = 0xFF;
			leftLED = 0;
			rightLED = 144;
		}
	}

	if(winTicks > 20)
	{
		if(gameStateRequest == REQUEST_RESET)
		{
			leftColor.blue = 0x00;
			leftColor.red = 0x00;
			leftColor.green = 0x00;
			rightColor.blue = 0x00;
			rightColor.red = 0x00;
			rightColor.green = 0x00;
			leftLED = 0;				//to turn off LED strips			
			rightLED = 0;
			returnValue = GAME_IDLE;
			winTicks = 0;
		}
	}
	else
	{
		winTicks++;
	}

	ledUARTsendColorValues(leftLED, rightLED);			//set LED strips

	return returnValue;
}

GAME_STATE_T getGameState(void)
{
	return gameState;
}

void getGameStateString(uint8_t* stateString)
{
	switch(gameState)
	{
		case GAME_INIT:
			sprintf((char*)stateString, "Game Init");
			break;

		case GAME_IDLE:
			sprintf(stateString, "Game Idle");
			break;

		case GAME_START:
			sprintf(stateString, "Game Start");
			break;

		case GAME_RUNNING:
			sprintf(stateString, "Game Running");
			break;

		case GAME_PAUSE:
			sprintf(stateString, "Game Pause");
			break;

		case GAME_ABORT:
			sprintf(stateString, "Game Abort");
			break;

		case GAME_WIN:
			sprintf(stateString, "Game Win");
			break;

		default:
		case GAME_UNKNOWN:
			sprintf(stateString, "Bad game state!");
			break;

	}
}

