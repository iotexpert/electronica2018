#ifndef LIQUID_LEVEL_H
#define LIQUID_LEVEL_H

#define SENSOR_STEP_VALUE 8
#define NUM_LEVEL_SENSORS 12


typedef union{
    struct{
        uint8_t leftLevel;
        uint8_t rightLevel;
        uint8_t dummya;
        uint8_t dummyb;
    }levelBytes;
        uint32_t levelWord;
}WATER_LEVEL_T;

//two globals:  left and right water level
extern uint8_t leftLevel;
extern uint8_t rightLevel;

extern void levelThread(wiced_thread_arg_t arg);

//extern void initLevelSense(void);
//extern void handleLevelSense(void);

//globally available print functions of level information
extern void reportRawLevels(void);
extern void reportLevels(void);
extern void reportRawLeftLevels(void);
extern void reportRawRightLevels(void);

#endif
