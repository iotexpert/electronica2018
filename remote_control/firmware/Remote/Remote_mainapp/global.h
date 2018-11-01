
#pragma once

#include "wiced.h"

/***************************************************************************
* Global constants
***************************************************************************/
/* States for the remote state machine */
#define INITSTATE (0)
#define CONNECTING (1)
#define CONNECTED (2)

/* Swipe directions */
#define RIGHT (0)
#define LEFT  (1)

/*******************************************************************************
* External Variables
*******************************************************************************/
extern wiced_bool_t   	nextState;
extern wiced_queue_t  	swipe_queue_handle;
extern wiced_mac_t 		mac; 	/* Device MAC address */

