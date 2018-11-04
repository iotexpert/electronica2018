
#pragma once

#include "wiced.h"

/***************************************************************************
* Constants and types
***************************************************************************/
/* LED states - LEDs are active low */
typedef enum{LED_OFF = 1u, LED_ON = 0u} LED_STATE;

/*******************************************************************************
* External Variables
*******************************************************************************/
extern wiced_mac_t 		mac; 	/* Device MAC address */

