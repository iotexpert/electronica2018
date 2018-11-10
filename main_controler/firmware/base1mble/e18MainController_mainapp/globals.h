#pragma once

//global queues for game
extern wiced_queue_t pumpRequestQueueHandle;
extern wiced_queue_t pumpCommandQueueHandle;
extern wiced_queue_t gameCommandQueueHandle;
extern wiced_event_flags_t startFlags;

#define START_FLAG_PUMP   (1<<0)
#define START_FLAG_LEVEL  (1<<1)
#define START_FLAG_AWS    (1<<2)
#define START_FLAG_BLE    (1<<3)
#define START_FLAG_GAME   (1<<4)
#define START_FLAG_ALL    (START_FLAG_PUMP|START_FLAG_LEVEL|START_FLAG_AWS|START_FLAG_BLE|START_FLAG_GAME)

#define MAX_WATER_LEVEL 75          //if water level exceeds this amount kill the pumps
#define PUMP_DIVISOR_FACTOR 1       // divisor of incoming pump request
#define PUMP_MINIMUM_SPEED 60       //pumps don't move much water below approx 40%
#define PUMP_DEFAULT_DECAY 1

#define GAME_WIN_LEVEL	70			//percent water level for a win to be triggered
