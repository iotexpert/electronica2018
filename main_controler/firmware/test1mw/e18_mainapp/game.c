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

static volatile GAME_STATE_T gameState = GAME_INIT;

extern uint8_t leftPumpRequest;
extern uint8_t rightPumpRequest;

START_PRESS_T startButtonPress = START_PRESS_NONE;

GAME_STATE_REQUEST_T gameStateRequest = REQUEST_NONE;
//extern GAME_STATE_REQUEST_T gameStateRequest;

//static void pumpIncrement(uint8 counts, PUMP_SELECT_T whichPump);
//void getGameStateString(uint8_t* stateString);

//game state machine thread
void gameStateMachine(wiced_thread_arg_t arg)
{
	static uint16_t stateTicks = 0;
	static uint8_t waterLevelTicks = 0;

	uint8_t gamePrintBfr[80];
	static volatile GAME_STATE_T previousState = GAME_UNKNOWN;

	//game state machine thread loop
	while(1)
	{
		//uncommenting this causes the application to crash
		//levelPublishRequest = AWS_PUBLISH_REQUEST;		//publish the water levels every loop iteration

		//check to see if a state change has occurred, if so dump to serial port
		if(previousState != gameState)
		{
			uint8_t stateString[40];
			getGameStateString(stateString);
			sprintf(gamePrintBfr, "\nChanging to state: %s state\n", stateString);
			previousState = gameState;
			WPRINT_APP_INFO((gamePrintBfr));

			//using this instead of the above causes the application to crash! why?
			//consolePrintGameState();
			//previousState = gameState;

		}

		//always check water levels
		//determineLevels();
		if(waterLevelTicks == LEVEL_PUBLISH_COUNTS)
		{
			levelPublishRequest = AWS_PUBLISH_REQUEST;		//publish the water levels every loop iteration
			waterLevelTicks = 0;
		}

		//and run the game state machine
		switch(gameState)
		{
			case GAME_INIT:
				switch(stateTicks)
				{
					case 0:
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
						gameState = GAME_IDLE;
						stateTicks=0;
						break;

					default:
						break;
				}
				stateTicks++;
				break;

			case GAME_IDLE:
				leftColor.blue = 0x00;
				leftColor.red = 0x00;
				leftColor.green = 0x00;
				rightColor.blue = 0x00;
				rightColor.red = 0x00;
				rightColor.green = 0x00;
				ledUARTsendColorValues(0, 0);			//set LED strips

				stateTicks++;
				if(stateTicks == 10)
				{
					stateTicks = 0;
					WPRINT_APP_INFO(("Still alive\n"));
					//reportLevels();
					//reportRawRightLevels();
					//reportRawLeftLevels();
					//reportRawLevels();
				}

				//sound test
				#ifdef IDLE_TEST_MODE
				if(getSoundState() == SOUND_IDLE)
				{
					playSound(resources_fight_wav_data);
				}
				#endif

				if(startButtonPress || gameStateRequest == REQUEST_START)
				{
					playSound(resources_fight_wav_data);
					gameState = GAME_START;
					startButtonPress = START_PRESS_NONE;
					#ifdef GAME_HARDWARE_TEST
					leftPumpRequest = 10;
					rightPumpRequest = 10;
					#else
					leftPumpRequest = 0;
					rightPumpRequest = 0;					
					#endif
					gameStateRequest = REQUEST_NONE;
				}
				break;

			case GAME_START:
				if(getSoundState() == SOUND_IDLE) gameState = GAME_RUNNING;

				if(gameStateRequest == REQUEST_ABORT)
				{
					gameState = GAME_ABORT;
					gameStateRequest = REQUEST_NONE;
				}
				break;

			case GAME_RUNNING:
				levelPublishRequest = AWS_PUBLISH_REQUEST;		//publish the water levels every loop iteration
				leftColor.blue = 0xFF;
				leftColor.red = 0x00;
				leftColor.green = 0x00;
				rightColor.blue = 0x00;
				rightColor.red = 0x00;
				rightColor.green = 0xFF;
				ledUARTsendColorValues(leftLevel, rightLevel);			//set LED strips
				kickPumps();

				if(startButtonPress || gameStateRequest == REQUEST_PAUSE)
				{
					stopAllPumps();
					gameState = GAME_PAUSE;
					startButtonPress = START_PRESS_NONE;
					gameStateRequest = REQUEST_NONE;
				}

				if(leftLevel > GAME_WIN_LEVEL || rightLevel > GAME_WIN_LEVEL)
				{
					stateTicks = 0;
					stopAllPumps();
					gameState = GAME_WIN;
				}

				if(gameStateRequest == REQUEST_ABORT)
				{
					gameState = GAME_ABORT;					
					gameStateRequest = REQUEST_NONE;
				}

				break;

			case GAME_PAUSE:
				if(startButtonPress || gameStateRequest == REQUEST_RESUME)
				{
					leftPumpRequest = 0;
					rightPumpRequest = 0;
					gameState = GAME_RUNNING;
					startButtonPress = START_PRESS_NONE;
					gameStateRequest = REQUEST_NONE;
				}

				if(gameStateRequest == REQUEST_ABORT)
				{
					gameStateRequest = REQUEST_NONE;
					gameState = GAME_ABORT;
				}
				break;

			case GAME_WIN:
				switch(stateTicks)
					{
						case 0:
							consolePrintWin();
							playSound(resources_winner_wav_data);
							if(leftLevel > rightLevel)
							{
								leftColor.blue = 0x00;
								leftColor.red = 0x00;
								leftColor.green = 0xFF;
								rightColor.blue = 0x00;
								rightColor.red = 0x00;
								rightColor.green = 0x00;
								ledUARTsendColorValues(144, 0);			//set LED strips
							}
							else
							{
								leftColor.blue = 0x00;
								leftColor.red = 0x00;
								leftColor.green = 0x00;
								rightColor.blue = 0x00;
								rightColor.red = 0x00;
								rightColor.green = 0xFF;
								ledUARTsendColorValues(0, 144);			//set LED strips
							}
							break;

						default:
								ledUARTsendColorValues(100, 100);			//set LED strips
							break;
					}
					if(stateTicks > 20)
					{
							if(gameStateRequest == REQUEST_RESET)
							{
								leftColor.blue = 0x00;
								leftColor.red = 0x00;
								leftColor.green = 0x00;
								rightColor.blue = 0x00;
								rightColor.red = 0x00;
								rightColor.green = 0x00;
								ledUARTsendColorValues(0, 0);			//set LED strips					
								gameState = GAME_IDLE;
							}
					}
				stateTicks++;
				break;

			default:
			case GAME_UNKNOWN:
			case GAME_ABORT:
				stopAllPumps();
				leftColor.blue = 0x00;
				leftColor.red = 0x00;
				leftColor.green = 0x00;
				rightColor.blue = 0x00;
				rightColor.red = 0x00;
				rightColor.green = 0x00;
				ledUARTsendColorValues(0, 0);			//set LED strips					

				if(gameStateRequest == REQUEST_RESET)
				{
					gameState = GAME_IDLE;
					gameStateRequest = REQUEST_NONE;
				}				
				break;
		}
		wiced_rtos_delay_milliseconds(GAME_MACHINE_DELAY);
	}
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

