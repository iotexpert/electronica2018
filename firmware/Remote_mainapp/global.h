
#pragma once

#include "wiced.h"

/***************************************************************************
* Constants and types
***************************************************************************/
/* LED states - LEDs are active low */
typedef enum{LED_OFF = 1u, LED_ON = 0u} LED_STATE;

/* Constants for the swipe queue */
#define SWIPE_MESSAGE_SIZE		(4)
#define SWIPE_QUEUE_SIZE		(100)

/* Swipe directions */
typedef enum{SWIPE_RIGHT, SWIPE_LEFT} SWIPE_DIR;

/* Constants for the display queue to pass messages */
#define DISPLAY_MESSAGE_SIZE	(4)
#define DISPLAY_QUEUE_SIZE		(10)

/*******************************************************************************
* External Variables
*******************************************************************************/
extern wiced_mac_t 		mac; 	/* Device MAC address */
extern wiced_queue_t	display_queue_handle;
extern wiced_queue_t  	swipe_queue_handle;

