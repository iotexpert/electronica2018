#pragma once


extern void levelThread(wiced_thread_arg_t arg);

//globally available print functions of level information; primarily for test/tuning
extern void reportRawLevels(void);
extern void reportLevels(void);
extern void reportRawLeftLevels(void);
extern void reportRawRightLevels(void);

extern uint32_t levelGetLeft();
extern uint32_t levelGetRight();
