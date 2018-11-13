#pragma once

// System Thread Handles
extern wiced_thread_t gameThreadHandle;
extern wiced_thread_t awsThreadHandle;
extern wiced_thread_t pumpThreadHandle;
extern wiced_thread_t levelThreadHandle;

//global queues for game
extern wiced_queue_t pumpRequestQueueHandle;
extern wiced_queue_t pumpCommandQueueHandle;
extern wiced_queue_t gameCommandQueueHandle;
extern wiced_event_flags_t startFlags;
extern wiced_event_flags_t buttonFlags;

#define TASK_FLAG_PUMP   (1<<0)
#define TASK_FLAG_LEVEL  (1<<1)
#define TASK_FLAG_AWS    (1<<2)
#define TASK_FLAG_BLE    (1<<3)
#define TASK_FLAG_GAME   (1<<4)
#define TASK_FLAG_ALL    (TASK_FLAG_PUMP|TASK_FLAG_LEVEL|TASK_FLAG_AWS|TASK_FLAG_BLE|TASK_FLAG_GAME)

#define BUTTON_FLAG_ARM   (1<<0)
#define BUTTON_FLAG_START (1<<1)

#define MAX_WATER_LEVEL 75          //if water level exceeds this amount kill the pumps
#define PUMP_DIVISOR_FACTOR 1       // divisor of incoming pump request
#define PUMP_MINIMUM_SPEED 70       //pumps don't move much water below approx 40%
#define PUMP_DEFAULT_DECAY 1

#define GAME_WIN_LEVEL	70			//percent water level for a win to be triggered
