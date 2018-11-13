/* Electronic game remote OLED Display and Button LEDs */

#pragma once

/***************************************************************************
* Constants and types
***************************************************************************/

/* Display queue messages. 1 byte command, 1 byte type, and 1 or 2 bytes data */
#define DISPLAY_CMD    0
#define DISPLAY_TYPE   1
#define DISPLAY_VAL1   2
#define DISPLAY_VAL2   3

/* Display Command - first byte in the queue */
enum {
	BLE_SCREEN,
	WIFI_SCREEN,
	GAME_SCREEN,
	SWIPE_VALUE
};

/* Type of update to make to the display second byte in the queue */
enum {
	BLE_START,
	BLE_ADVERTISE,
	BLE_CONNECT,
	REGISTER_NOTIFY,
	WIFI_CONNECT,
	AWS_RESOURCES,
	AWS_CONNECT,
	SUBSCRIBE_SHADOW,
	INIT_WIFI,
	INIT_BLE,
	WATER_VALUE
};

/*******************************************************************************
* External Functions
*******************************************************************************/
extern void displayThread(void);
