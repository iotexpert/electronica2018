/* Electronic game remote CapSense */

#pragma once

/***************************************************************************
* Constants and types
***************************************************************************/
/* Constants for the queue to pass swipe messages. 1st byte is direction, 2nd byte is value (last bytes are reserved) */
#define SWIPE_MESSAGE_SIZE		(4)
#define SWIPE_QUEUE_SIZE		(100)

/* Swipe directions */
typedef enum{SWIPE_RIGHT, SWIPE_LEFT} SWIPE_DIR;

/*******************************************************************************
* External Variables
*******************************************************************************/
extern wiced_queue_t  	swipe_queue_handle;

/*******************************************************************************
* External Functions
*******************************************************************************/
extern void capSenseThread(void);

