/* Electronic game remote OLED Display and Button LEDs */

#pragma once

/***************************************************************************
* Constants and types
***************************************************************************/
/* Constants for the queue to pass  messages. Start queue to accept messages. */
#define DISPLAY_MESSAGE_SIZE	(4)
#define DISPLAY_QUEUE_SIZE		(10)

/* The messages are 1 byte command, 1 byte type, and 1 or 2 bytes data */
#define DISPLAY_CMD    0
#define DISPLAY_TYPE   1
#define DISPLAY_VAL1   2
#define DISPLAY_VAL2   3

/* Display Command - used in the queue */
enum {
	BLE_SCREEN,
	WIFI_SCREEN,
	GAME_SCREEN,
	SWIPE_VALUE
};

/* Type of update to make to the display - the exact update depends on the screen - value passed in queue */
enum {
	INIT,
	ADVERTISE,
	BLE_CONNECT,
	REGISTER_NOTIFY,
	WIFI_CONNECT,
	MQTT_CONNECT,
	SUBSCRIBE_SHADOW,
	WATER_VALUE
};

/*******************************************************************************
* External Variables
*******************************************************************************/
extern wiced_queue_t	display_queue_handle;

/*******************************************************************************
* External Functions
*******************************************************************************/
extern void displayThread(void);
