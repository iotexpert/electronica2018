#ifndef LIQUID_LEVEL_H
#define LIQUID_LEVEL_H

#define THRESHOLD_LEVEL 2300
#define SENSOR_STEP_VALUE 8
#define NUM_LEVEL_SENSORS 12


extern void initLevelSense(void);
extern void handleLevelSense(void);
extern void determineLevels(void);
extern void reportRawLevels(void);
extern void reportLevels(void);
extern void reportRawLeftLevels(void);
extern void reportRawRightLevels(void);

#endif