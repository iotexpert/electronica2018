#ifndef LIQUID_LEVEL_H
#define LIQUID_LEVEL_H

//two globals:  left and right water level
extern uint8_t leftLevel;
extern uint8_t rightLevel;

extern void levelThread(wiced_thread_arg_t arg);

//globally available print functions of level information; primarily for test/tuning
extern void reportRawLevels(void);
extern void reportLevels(void);
extern void reportRawLeftLevels(void);
extern void reportRawRightLevels(void);

#endif
