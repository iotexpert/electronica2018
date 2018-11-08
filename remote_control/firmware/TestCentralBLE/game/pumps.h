/*
 * pumps.h
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#ifndef SOURCE_PUMPS_H_
#define SOURCE_PUMPS_H_


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

typedef enum{
	LEFT_PUMP,
	RIGHT_PUMP
}PUMP_SELECT_T;


//global queues for game 
extern wiced_queue_t pumpRequestQueueHandle;
extern wiced_queue_t pumpCommandQueueHandle;

//globally available functions
extern void pumpThread(wiced_thread_arg_t arg);
extern void stopAllPumps(void);                     //globally available so other threads can do pump halt if necessary
extern void kickPumps(PUMP_REQUEST_T* pumpRequest); //globally available so command console can do low level pump testing

#endif /* SOURCE_PUMPS_H_ */
