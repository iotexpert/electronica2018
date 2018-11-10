/*
 * pumps.c
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#include "wiced.h"
#include "cycfg_peripherals.h"
#include "pumps.h"
#include "cycfg_pins.h"
#include "game.h"
#include "liquidlevel.h"
#include "globals.h"

//constants


//see page 4 of TB6612FNG datasheet
typedef enum{
	PUMP_SHORT_BRAKE,
	PUMP_RUN_CCW,
	PUMP_RUN_CW,
	PUMP_STOP
}PUMP_CONTROL_T;

//global variables
static uint8_t leftSpeed = 0;       //pump speed in PWM percentage
static uint8_t rightSpeed = 0;
static uint32_t pumpDecayFactor=PUMP_DEFAULT_DECAY; // Default Decay Value


//local function prototypes
static void pumpDecay(void);
static void stopPump(pumps_select_t whichPump);
static void pumpControl(pumps_select_t pump, PUMP_CONTROL_T control);
static void pumpsKick(pumps_speed_request_t* pumpRequest);
static void pumpDecay(void);
static void stopPump(pumps_select_t whichPump);
static void pumpsEnable(void);
//static void pumpsDisable(void);
static void pumpsSetSpeed(pumps_select_t whichPump, uint8_t speed);
static void pumpControl(pumps_select_t pump, PUMP_CONTROL_T control);


//code
void pumpsThread(wiced_thread_arg_t arg)
{

	//left pump pwm hardware
	Cy_TCPWM_PWM_Init(leftPump_HW, leftPump_NUM, &leftPump_config);
	Cy_TCPWM_PWM_Enable(leftPump_HW, leftPump_NUM);
	Cy_TCPWM_TriggerStart(leftPump_HW, leftPump_MASK);

	//right pump pwm hardware
	Cy_TCPWM_PWM_Init(rightPump_HW, rightPump_NUM, &rightPump_config);
	Cy_TCPWM_PWM_Enable(rightPump_HW, rightPump_NUM);
	Cy_TCPWM_TriggerStart(rightPump_HW, rightPump_MASK);

	//set correct h-bridge control outputs
	pumpControl(LEFT_PUMP, PUMP_RUN_CCW);
	pumpControl(RIGHT_PUMP, PUMP_RUN_CCW);

	wiced_rtos_set_event_flags(	&startFlags,	START_FLAG_PUMP);

	while(1)
	{
		pumps_command_request_t pumpsCommandRequest;
		if(wiced_rtos_is_queue_empty(&pumpCommandQueueHandle) == WICED_ERROR)      //if queue is not empty...
		{
			wiced_rtos_pop_from_queue(&pumpCommandQueueHandle, &pumpsCommandRequest, WICED_NO_WAIT);
			switch(pumpsCommandRequest.pumpCommand)
			{
			case PUMPS_DISABLE:
				pumpsStopAll();

				break;
			case PUMPS_ENABLE:
				pumpsEnable();
				break;
			case PUMPS_DECAY:
				pumpDecayFactor = pumpsCommandRequest.val;
				break;
			}

		}

		if(wiced_rtos_is_queue_empty(&pumpRequestQueueHandle) == WICED_ERROR)      //if queue is not empty...)
		{
			pumps_speed_request_t message;
			wiced_rtos_pop_from_queue(&pumpRequestQueueHandle, &message, WICED_NO_WAIT);

			pumps_speed_request_t pumpRequest;
			pumpRequest.pumpWord = message.pumpWord;
			pumpsKick(&pumpRequest);
		}

		pumpDecay();                        //during game play the pump speed decays
		wiced_rtos_delay_milliseconds(50);  //sleep for 50ms
	}
}


//void kickPumps(void)
static void pumpsKick(pumps_speed_request_t* pumpRequest)
{
	uint8_t leftPumpRequest = (pumpRequest->pumpBytes.leftPumpRequest)/PUMP_DIVISOR_FACTOR;
	uint8_t rightPumpRequest = (pumpRequest->pumpBytes.rightPumpRequest)/PUMP_DIVISOR_FACTOR;

	if(leftPumpRequest)
	{
		if(leftSpeed < PUMP_MINIMUM_SPEED)
		{
			leftSpeed = PUMP_MINIMUM_SPEED;
		}
		else
		{
			if(leftSpeed < 100 - leftPumpRequest)
			{
				leftSpeed += leftPumpRequest;
			}
			else
			{
				leftSpeed = 100;
			}
		}
	}

	if(rightPumpRequest)
	{
		if(rightSpeed < PUMP_MINIMUM_SPEED)
		{
			rightSpeed = PUMP_MINIMUM_SPEED;
		}
		else
		{
			if(rightSpeed < 100 - rightPumpRequest)
			{
				rightSpeed += rightPumpRequest;
			}
			else
			{
				rightSpeed = 100;
			}
		}
	}

	pumpsSetSpeed(LEFT_PUMP, leftSpeed);
	pumpsSetSpeed(RIGHT_PUMP, rightSpeed);
}

static void pumpDecay(void)
{
	if(leftSpeed > 0) leftSpeed = leftSpeed - pumpDecayFactor;
	if(rightSpeed > 0) rightSpeed = rightSpeed - pumpDecayFactor;
	pumpsSetSpeed(LEFT_PUMP, leftSpeed);
	pumpsSetSpeed(RIGHT_PUMP, rightSpeed);
}


static void stopPump(pumps_select_t whichPump)
{
	switch(whichPump)
	{
	case LEFT_PUMP:
		leftSpeed = 0;
		pumpsSetSpeed(LEFT_PUMP, leftSpeed);
		break;

	case RIGHT_PUMP:
		rightSpeed = 0;
		pumpsSetSpeed(RIGHT_PUMP, rightSpeed);
		break;

	default:
		break;
	}
}

static void pumpsEnable(void)
{
	Cy_GPIO_Write(pumpEnable_PORT, pumpEnable_PIN, 1);	//enable pump h-bridge

}

#if 0
static void pumpsDisable(void)
{
	Cy_GPIO_Write(pumpEnable_PORT, pumpEnable_PIN, 0);	//disable pump h-bridge

}
#endif


void pumpsStopAll(void)
{
	stopPump(LEFT_PUMP);
	stopPump(RIGHT_PUMP);

}

static void pumpsSetSpeed(pumps_select_t whichPump, uint8_t speed)
{
	switch(whichPump)
	{
	case LEFT_PUMP:
		Cy_TCPWM_Counter_SetCompare0(leftPump_HW, leftPump_NUM, speed);
		break;

	case RIGHT_PUMP:
		Cy_TCPWM_Counter_SetCompare0(rightPump_HW, rightPump_NUM, speed);
		break;

	default:
		break;
	}
}


static void pumpControl(pumps_select_t pump, PUMP_CONTROL_T control)
{
	//I always debate whether this should be two functions or one; the nature
	//of dealig with hardware means redundant code
	switch(pump)
	{
	case LEFT_PUMP:
		switch(control)
		{
		case PUMP_SHORT_BRAKE:
			Cy_GPIO_Write(leftPumpIN1_PORT, leftPumpIN1_PIN, 1);
			Cy_GPIO_Write(leftPumpIN2_PORT, leftPumpIN2_PIN, 1);
			break;

		case PUMP_RUN_CCW:
			Cy_GPIO_Write(leftPumpIN1_PORT, leftPumpIN1_PIN, 0);
			Cy_GPIO_Write(leftPumpIN2_PORT, leftPumpIN2_PIN, 1);
			break;

		case PUMP_RUN_CW:
			Cy_GPIO_Write(leftPumpIN1_PORT, leftPumpIN1_PIN, 1);
			Cy_GPIO_Write(leftPumpIN2_PORT, leftPumpIN2_PIN, 0);
			break;

		default:
		case PUMP_STOP:
			Cy_GPIO_Write(leftPumpIN1_PORT, leftPumpIN1_PIN, 0);
			Cy_GPIO_Write(leftPumpIN2_PORT, leftPumpIN2_PIN, 0);
			break;
		}

		break;

		case RIGHT_PUMP:
			switch(control)
			{
			case PUMP_SHORT_BRAKE:
				Cy_GPIO_Write(rightPumpIN1_PORT, rightPumpIN1_PIN, 1);
				Cy_GPIO_Write(rightPumpIN2_PORT, rightPumpIN2_PIN, 1);
				break;

			case PUMP_RUN_CCW:
				Cy_GPIO_Write(rightPumpIN1_PORT, rightPumpIN1_PIN, 0);
				Cy_GPIO_Write(rightPumpIN2_PORT, rightPumpIN2_PIN, 1);
				break;

			case PUMP_RUN_CW:
				Cy_GPIO_Write(rightPumpIN1_PORT, rightPumpIN1_PIN, 1);
				Cy_GPIO_Write(rightPumpIN2_PORT, rightPumpIN2_PIN, 0);
				break;

			default:
			case PUMP_STOP:
				Cy_GPIO_Write(rightPumpIN1_PORT, rightPumpIN1_PIN, 0);
				Cy_GPIO_Write(rightPumpIN2_PORT, rightPumpIN2_PIN, 0);
				break;
			}
			break;

			default:
				break;
	}
}

///////////////////// RTOS Helpers /////////

void pumpsSendEnable(void)
{
	pumps_command_request_t request;
	request.pumpCommand = PUMPS_ENABLE;
	wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &request, WICED_WAIT_FOREVER);
}

void pumpsSendDisable(void)
{
	pumps_command_request_t request;
	request.pumpCommand = PUMPS_DISABLE;
	wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &request, WICED_WAIT_FOREVER);
}


void pumpsSendValues(uint8_t left, uint8_t right)
{
	pumps_speed_request_t pumpRequest;
	pumpRequest.pumpBytes.leftPumpRequest = left;
	pumpRequest.pumpBytes.rightPumpRequest = right;
    wiced_rtos_push_to_queue(&pumpRequestQueueHandle, &pumpRequest.pumpWord, WICED_NO_WAIT); /* Push value onto queue*/

}

void pumpsSendDecay(uint32_t decayValue)
{
	pumps_command_request_t request;
	request.pumpCommand = PUMPS_DECAY;
	request.val = decayValue;
	wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &request, WICED_WAIT_FOREVER);
}



