/*
 * pumps.h
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#ifndef SOURCE_PUMPS_H_
#define SOURCE_PUMPS_H_

//#define PUMP_KICK_FACTOR 10
#define PUMP_DIVISOR_FACTOR 4
#define PUMP_DECAY_FACTOR 2
#define PUMP_MINIMUM_SPEED 50

typedef enum{
	PUMP_BRAKE,
	PUMP_CW,
	PUMP_CCW
}PUMP_DIRECTION_T;

typedef enum{
	LEFT_PUMP,
	RIGHT_PUMP
}PUMP_SELECT_T;

//see page 4 of TB6612FNG datasheet
typedef enum{
    PUMP_SHORT_BRAKE,
    PUMP_RUN_CCW,
    PUMP_RUN_CW,
    PUMP_STOP
}PUMP_CONTROL_T;

typedef union{
    struct{
        uint8_t leftPumpRequest;
        uint8_t rightPumpRequest;
        uint8_t dummya;
        uint8_t dummyb;
    }pumpBytes;
        uint32_t pumpWord;
}PUMP_REQUEST_T;

enum{
	PUMPS_DISABLED,
	PUMPS_ENABLED
};

//global queues for game 
extern wiced_queue_t pumpRequestQueueHandle;
extern wiced_queue_t pumpCommandQueueHandle;

extern void pumpThread(wiced_thread_arg_t arg);


void initPumpHW(void);
//void kickPump(PUMP_SELECT_T whichPump, uint8_t counts);
extern void stopAllPumps(void);
extern void pumpDecay(void);
void kickPumps(PUMP_REQUEST_T* pumpRequest);


void setPumpDirection(PUMP_SELECT_T whichPump, PUMP_DIRECTION_T whatWay);
void stopPump(PUMP_SELECT_T whichPump);
void setPumpSpeed(PUMP_SELECT_T whichPump, uint8_t speed);
void pumpControl(PUMP_SELECT_T pump, PUMP_CONTROL_T control);

#endif /* SOURCE_PUMPS_H_ */
