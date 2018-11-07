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

//constants
#define PUMP_DIVISOR_FACTOR 3       // divisor of incoming pump request
#define PUMP_DECAY_FACTOR 2         // -percent per 50ms
#define PUMP_MINIMUM_SPEED 50       //pumps don't move much water below approx 40%
#define MAX_WATER_LEVEL 90          //if water level exceeds this amount kill the pumps

//typedefs
typedef enum{
	PUMP_BRAKE,
	PUMP_CW,
	PUMP_CCW
}PUMP_DIRECTION_T;

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

//local function prototypes
void pumpDecay(void);
void setPumpDirection(PUMP_SELECT_T whichPump, PUMP_DIRECTION_T whatWay);
void stopPump(PUMP_SELECT_T whichPump);
void setPumpSpeed(PUMP_SELECT_T whichPump, uint8_t speed);
void pumpControl(PUMP_SELECT_T pump, PUMP_CONTROL_T control);

//code
void pumpThread(wiced_thread_arg_t arg)
{
    static uint8_t pumpEnableState = PUMPS_DISABLED;

    //left pump pwm hardware
    Cy_TCPWM_PWM_Init(leftPump_HW, leftPump_NUM, &leftPump_config);
    Cy_TCPWM_PWM_Enable(leftPump_HW, leftPump_NUM);
    Cy_TCPWM_TriggerStart(leftPump_HW, leftPump_MASK);

    //right pump pwm hardware
    Cy_TCPWM_PWM_Init(rightPump_HW, rightPump_NUM, &rightPump_config);
    Cy_TCPWM_PWM_Enable(rightPump_HW, rightPump_NUM);
    Cy_TCPWM_TriggerStart(rightPump_HW, rightPump_MASK);

    //set correct h-bridge control outputs
    pumpControl(LEFT_PUMP, PUMP_CW);
    pumpControl(RIGHT_PUMP, PUMP_CW);

    while(1)
    {
        uint32_t message;
        if(wiced_rtos_is_queue_empty(&pumpCommandQueueHandle) == WICED_ERROR)      //if queue is not empty...
        {
            wiced_rtos_pop_from_queue(&pumpCommandQueueHandle, &message, WICED_NO_WAIT);
            pumpEnableState = (uint8_t) message;
        }

        if(wiced_rtos_is_queue_empty(&pumpRequestQueueHandle) == WICED_ERROR)      //if queue is not empty...)
        {
            wiced_rtos_pop_from_queue(&pumpRequestQueueHandle, &message, WICED_NO_WAIT);
            PUMP_REQUEST_T pumpRequest;
            pumpRequest.pumpWord = message;
            if(pumpEnableState == PUMPS_ENABLED)
            {
                kickPumps(&pumpRequest);
            }
        }

        if(pumpEnableState == PUMPS_DISABLED)
        {
            stopAllPumps();                        
        }

        if(leftLevel > MAX_WATER_LEVEL || rightLevel > MAX_WATER_LEVEL)
        {
            pumpEnableState = PUMPS_DISABLED;
            stopAllPumps();            
        }

		pumpDecay();                        //during game play the pump speed decays
        wiced_rtos_delay_milliseconds(50);  //sleep for 50ms        
    }
}


//void kickPumps(void)
void kickPumps(PUMP_REQUEST_T* pumpRequest)
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

    setPumpSpeed(LEFT_PUMP, leftSpeed);
    setPumpSpeed(RIGHT_PUMP, rightSpeed);
}

void pumpDecay(void)
{
    if(leftSpeed > 0) leftSpeed = leftSpeed - PUMP_DECAY_FACTOR;
    if(rightSpeed > 0) rightSpeed = rightSpeed - PUMP_DECAY_FACTOR;
    setPumpSpeed(LEFT_PUMP, leftSpeed);
    setPumpSpeed(RIGHT_PUMP, rightSpeed);
}


// void setPumpDirection(PUMP_SELECT_T whichPump, PUMP_DIRECTION_T whatWay)
// {
// 	switch(whichPump)
// 	{
// 		case LEFT_PUMP:

// 			break;

// 		case RIGHT_PUMP:
// 			break;

// 		default:
// 			break;
// 	}

// }

void stopPump(PUMP_SELECT_T whichPump)
{
	switch(whichPump)
	{
		case LEFT_PUMP:
            leftSpeed = 0;
            setPumpSpeed(LEFT_PUMP, leftSpeed);
			break;

		case RIGHT_PUMP:
            rightSpeed = 0;
            setPumpSpeed(RIGHT_PUMP, rightSpeed);
			break;

		default:
			break;
	}
}

void stopAllPumps(void)
{
	stopPump(LEFT_PUMP);
	stopPump(RIGHT_PUMP);
}

void setPumpSpeed(PUMP_SELECT_T whichPump, uint8_t speed)
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


void pumpControl(PUMP_SELECT_T pump, PUMP_CONTROL_T control)
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

