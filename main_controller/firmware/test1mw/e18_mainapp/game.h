/*
 * game.h
 *
 *  Created on: Sep 13, 2018
 *      Author: kmwh
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "cy_pdl.h"
#include "wiced.h"

#define FW_VERSION_MAJOR '0'
#define FW_VERSION_MINOR '1'


#define GAME_MACHINE_DELAY	125		//time in milliseconds of delay for game machine thread
#define LEVEL_PUBLISH_COUNTS 3		//number of times through game machine loop to publish water levels on AWS

#define GAME_WIN_LEVEL	70			//percent water level for a win to be triggered

//#define GAME_HARDWARE_TEST			//define this to start the pumps on game start for hardware test

typedef enum{
	GAME_UNKNOWN,
	GAME_INIT,
	GAME_IDLE,
	GAME_START,
	GAME_RUNNING,
	GAME_PAUSE,
	GAME_ABORT,
	GAME_WIN
}GAME_STATE_T;

typedef enum{
	REQUEST_NONE,
	REQUEST_START,
	REQUEST_PAUSE,
	REQUEST_RESUME,
	REQUEST_ABORT,
	REQUEST_RESET,
	REQUEST_DEMO_1,
	REQUEST_DEMO_2,
	REQUEST_STOP_DEMO
}GAME_STATE_REQUEST_T;

typedef enum{
	START_PRESS_NONE,
	START_PRESS_TRUE
}START_PRESS_T;


extern uint8_t leftLevel;
extern uint8_t rightLevel;
extern uint8_t leftPumpRequest;
extern uint8_t rightPumpRequest;
extern uint32_t systicks;
extern GAME_STATE_REQUEST_T gameStateRequest;
extern START_PRESS_T startButtonPress;

extern void gameStateMachine(wiced_thread_arg_t arg);
extern void getGameStateString(uint8_t* stateString);
extern GAME_STATE_T getGameState(void);

#endif /* SRC_GAME_H_ */
