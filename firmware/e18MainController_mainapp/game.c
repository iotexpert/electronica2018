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
#include "ble_app.h" /* GJL */
#include "pumps.h"
#include "game_console.h"
#include "leduart.h"
#include "resources.h"
#include "liquidlevel.h"
#include "globals.h"
#include "sound.h"

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



//game state machine defines
#define GAME_MACHINE_DELAY	100		//time in milliseconds of delay for game machine thread

//variables
static game_state_t gameState = GAME_INIT;			    //the game state
static game_state_t gameStateNext = GAME_INIT;			//the next game state

typedef enum {
	WINNER_NONE,
	WINNER_LEFT,
	WINNER_RIGHT
} game_winner_t;

static game_winner_t gameWinner;

void gameStateRequest(game_state_t state)
{
	game_command_request_t request;
	request.desiredState = state;
	wiced_rtos_push_to_queue(&gameCommandQueueHandle, &request, 0);

}
game_state_t gameGetState(void)
{
	return gameState;
}

void gameGetString(char *stateString)
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

	case GAME_WIN:
		sprintf(stateString, "Game Win");
		break;

	}
}

void gameLedTimerHandler(void *arg)
{
	static uint32_t counter=0;

	counter += 1;

	switch(gameState)
	{
	case GAME_START:
	case GAME_RUNNING:
	case GAME_PAUSE:
		leftColor.blue = 0xFF;
		leftColor.red = 0x00;
		leftColor.green = 0x00;
		rightColor.blue = 0x00;
		rightColor.red = 0xFF;
		rightColor.green = 0x00;
		ledUARTsendColorValues(levelGetLeft(), levelGetRight());
		break;

	case GAME_WIN:
		leftColor.blue = (gameWinner == WINNER_LEFT)?0xFF:0;
		leftColor.red = 0x00;
		leftColor.green = 0x00;
		rightColor.blue = 0x00;
		rightColor.red = (gameWinner == WINNER_LEFT)?0:0xFF;
		rightColor.green = 0x00;

		if(counter % 2)
			ledUARTsendColorValues((gameWinner == WINNER_LEFT)?100:0, (gameWinner == WINNER_LEFT)?0:100);
		else
			ledUARTsendColorValues(0,0);
		break;

	case GAME_INIT:
	case GAME_IDLE:
		leftColor.blue = rand() % 0xFF;
		leftColor.red = rand() % 0xFF;
		leftColor.green = rand() % 0xFF ;
		rightColor.blue = rand() % 0xFF;
		rightColor.red = rand() % 0xFF ;
		rightColor.green = rand() % 0xFF;
		ledUARTsendColorValues(rand() % 100,rand() % 100);
		break;
	}
}

void buttonArmHandler(void *arg)
{

//	WPRINT_APP_INFO(("arm = %d\n",Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN)));

	if(Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN))
	{
		pumpsStopAll();
	}
}

void buttonStartHandler(void *arg)
{
	static uint32_t lastPress=0;
	if(Cy_GPIO_Read(startButton_PORT, startButton_PIN))
			return;

	if(tx_time_get()<lastPress+100)
		return;
	lastPress = tx_time_get();
	wiced_rtos_set_event_flags(	&buttonFlags,BUTTON_FLAG_START);
}

void gameThread(wiced_thread_arg_t arg)
{
	gameState = GAME_INIT;
	gameStateNext = GAME_INIT;

	srand(tx_time_get());

	uint32_t loopCounter=0;

	wiced_timer_t ledTimerHandle;
	wiced_rtos_init_timer (&ledTimerHandle, 100, gameLedTimerHandler, 0);
	wiced_rtos_start_timer(&ledTimerHandle);

    wiced_gpio_input_irq_enable(	WICED_GPIO_50,IRQ_TRIGGER_FALLING_EDGE,buttonArmHandler,0);
    wiced_gpio_input_irq_enable(	WICED_GPIO_49,IRQ_TRIGGER_RISING_EDGE,buttonStartHandler,0);

	while(1)
	{
	    uint32_t tempButtonFlags;

		if(wiced_rtos_is_queue_empty(&gameCommandQueueHandle) == WICED_ERROR)      //if queue is not empty...
		{
			game_command_request_t gameCommandRequest;
			wiced_rtos_pop_from_queue(&gameCommandQueueHandle, &gameCommandRequest, WICED_NO_WAIT);
			gameStateNext = gameCommandRequest.desiredState;
			if(gameStateNext == GAME_RUNNING)
				pumpsSendEnable();
			else
				pumpsSendDisable();
		}

		gameState = gameStateNext;

		// Get the button Event Flag to see if the start button was pressed
		tempButtonFlags = 0;
		wiced_rtos_wait_for_event_flags(&buttonFlags,(uint32_t)(BUTTON_FLAG_START),&tempButtonFlags,WICED_TRUE,WAIT_FOR_ANY_EVENT,0);

		switch(gameState)
		{
		case GAME_INIT:
			Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
			Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
			wiced_rtos_delay_milliseconds(500);
			pumpsSendEnable();
			pumpsSendValues(100,100);
			wiced_rtos_delay_milliseconds(750);
			Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_OFF);	//turn on arm switch LED
			Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_OFF);	//turn on arm switch LED
			pumpsSendDisable();
			gameStateNext = GAME_IDLE;
			break;

		case GAME_IDLE:
			Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_OFF);
			if((tempButtonFlags & BUTTON_FLAG_START) && Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN) == SWITCH_ON)
			{
				soundPlay(resources_fight_wav_data);
				/* GJL: Disable BLE scanning during the game */
				bleScanMode(WICED_FALSE);
				gameStateNext = GAME_START;
				WPRINT_APP_INFO(("switching to start\n"));
			}
			gameWinner = WINNER_NONE;
			break;
		case GAME_START:
			srand(tx_time_get());

			Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_ON);
			if(getSoundState() == SOUND_IDLE)
			{
				pumpsSendEnable();
				WPRINT_APP_INFO(("switching to running\n"));

				gameStateNext = GAME_RUNNING;
			}
			break;
		case GAME_RUNNING:
			Cy_GPIO_Write(startLED_PORT, startLED_PIN, EXTERNAL_LED_ON);

			if(levelGetLeft()>GAME_WIN_LEVEL || levelGetRight()>GAME_WIN_LEVEL)
			{
				if(levelGetLeft()>GAME_WIN_LEVEL)
					gameWinner = WINNER_LEFT;
				else
					gameWinner = WINNER_RIGHT;

				pumpsSendDisable();
				soundPlay(resources_winner_wav_data);
				gameStateNext = GAME_WIN;
			}

			if(tempButtonFlags & BUTTON_FLAG_START) // Did they press the start button
			{
				WPRINT_APP_INFO(("switching to pause\n"));
				pumpsSendDisable();
				gameStateNext = GAME_PAUSE;
			}
			break;
		case GAME_PAUSE:
			if(loopCounter % 3 == 0) // blink every third time through the loop
				Cy_GPIO_Inv(startLED_PORT, startLED_PIN);

			if(tempButtonFlags & BUTTON_FLAG_START) // Did they press the start button
			{
				WPRINT_APP_INFO(("switching to running\n"));
				pumpsSendEnable();
				gameStateNext = GAME_RUNNING;
			}
			break;

		case GAME_WIN:
			if(getSoundState() == SOUND_IDLE)
			{
				wiced_rtos_delay_milliseconds(5000); // hold for 2 seconds to leave lights on.
				/* GJL: Allow BLE scanning again once the game is done */
				bleScanMode(WICED_TRUE);
				gameStateNext = GAME_IDLE;
			}
			break;
		}

		// This is wasteful to do every time through the loop... but oh well
		if(Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN) == SWITCH_ON)
			Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_ON);	//turn on arm switch LED
		else
			Cy_GPIO_Write(armLED_PORT, armLED_PIN, EXTERNAL_LED_OFF);	//turn on arm switch LED

		// Whatever happens if the switch is off... turn everything off.
		if(Cy_GPIO_Read(armSwitch_PORT, armSwitch_PIN) == SWITCH_OFF && gameState != GAME_IDLE)
		{
			pumpsStopAll();
			gameStateNext = GAME_IDLE;
		}

		loopCounter += 1;
		wiced_rtos_delay_milliseconds(GAME_MACHINE_DELAY);
	}
}
