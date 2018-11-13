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

typedef enum{
	GAME_INIT,
	GAME_IDLE,
	GAME_START,
	GAME_RUNNING,
	GAME_PAUSE,
	GAME_WIN
} game_state_t;

typedef struct {
	game_state_t desiredState;
} game_command_request_t;

extern void gameThread(wiced_thread_arg_t arg);
extern void gameGetString(char *stateString);
extern game_state_t gameGetState(void);
extern void gameStateRequest(game_state_t);

#endif /* SRC_GAME_H_ */
