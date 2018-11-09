#pragma once

//global queues for game
extern wiced_queue_t pumpRequestQueueHandle;
extern wiced_queue_t pumpCommandQueueHandle;

#define MAX_WATER_LEVEL 70          //if water level exceeds this amount kill the pumps
#define PUMP_DIVISOR_FACTOR 1       // divisor of incoming pump request
#define PUMP_MINIMUM_SPEED 60       //pumps don't move much water below approx 40%
#define PUMP_DEFAULT_DECAY 1

