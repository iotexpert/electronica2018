/*
 * pumps.h
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#ifndef SOURCE_PUMPS_H_
#define SOURCE_PUMPS_H_

#define PUMP_KICK_FACTOR 10
#define PUMP_DECAY_FACTOR 5

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


extern void initPumpHW(void);
extern void kickPump(PUMP_SELECT_T whichPump, uint8_t counts);
extern void stopAllPumps(void);
extern void pumpDecay(void);

void setPumpDirection(PUMP_SELECT_T whichPump, PUMP_DIRECTION_T whatWay);
void stopPump(PUMP_SELECT_T whichPump);
void setPumpSpeed(PUMP_SELECT_T whichPump, uint8_t speed);
void pumpControl(PUMP_SELECT_T pump, PUMP_CONTROL_T control);

#endif /* SOURCE_PUMPS_H_ */
