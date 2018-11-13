/*
 * pumps.c
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#include "cycfg_peripherals.h"
#include "pumps.h"
#include "cycfg_pins.h"
#include "game.h"


static uint8_t leftSpeed = 0;
static uint8_t rightSpeed = 0;


void initPumpHW(void)
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
    pumpControl(LEFT_PUMP, PUMP_CW);
    pumpControl(RIGHT_PUMP, PUMP_CW);
}

// kickPumps for testing
// void kickPumps(void)
// {
//     if(leftPumpRequest)
//     {
//         leftSpeed = 100;
//         leftPumpRequest = 0;
//     }
    
//     if(rightPumpRequest)
//     {
//         rightSpeed = 100;
//         rightPumpRequest = 0;
//     }

//     setPumpSpeed(LEFT_PUMP, leftSpeed);
//     setPumpSpeed(RIGHT_PUMP, rightSpeed);
// }

void kickPumps(void)
{
    while(leftPumpRequest)
    {
        if(leftSpeed < 30)
        {
            leftSpeed = 30;
        }
        else
        {
            if(leftSpeed < 100 - PUMP_KICK_FACTOR)
            {
                leftSpeed = leftSpeed + PUMP_KICK_FACTOR;
            }
            else
            {
                leftSpeed = 100;
            }
        }
        leftPumpRequest--;
    }

    while(rightPumpRequest)
    {
        if(rightSpeed < 30)
        {
            rightSpeed = 30;
        }
        else
        {
            if(rightSpeed < 100 - PUMP_KICK_FACTOR)
            {
                rightSpeed = rightSpeed + PUMP_KICK_FACTOR;
            }
            else
            {
                rightSpeed = 100;
            }
        }
        rightPumpRequest--;
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


void setPumpDirection(PUMP_SELECT_T whichPump, PUMP_DIRECTION_T whatWay)
{
	switch(whichPump)
	{
		case LEFT_PUMP:

			break;

		case RIGHT_PUMP:
			break;

		default:
			break;
	}

}

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

