/* Electronica 2018 Game Remote */

#include "global.h"
#include "wiced.h"
#include "capsense_app.h"
#include "display_app.h"

#include "wiced_bt_dev.h"
#include "wiced_bt_ble.h"
#include "wiced_bt_cfg.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_stack.h"
#include "ble_app.h"
#include "ble_db.h"

/******************************************************
 *                      Macros
 ******************************************************/
/* Thread parameters */
#define CAPSENSE_PRIORITY (7)
#define CAPSENSE_THREAD_STACK_SIZE (5*1024UL)
#define DISPLAY_PRIORITY (7)
#define DISPLAY_THREAD_STACK_SIZE (5*1024UL)

/******************************************************
 *               Variable Definitions
 ******************************************************/
wiced_mac_t mac; 	/* Device MAC address */
/* RTOS structures */
static wiced_thread_t capsense_thread_handle;
static wiced_thread_t display_thread_handle;
wiced_queue_t  		  swipe_queue_handle;
wiced_queue_t	      display_queue_handle;

/*******************************************************************************
* Function Definitions
*******************************************************************************/
void application_start( void )
{
    wiced_init( );

	/* Get device MAC Address to be used in AWS Thing name or Bluetooth device address */
    wiced_wifi_get_mac_address(&mac);
    WPRINT_APP_INFO(("MAC Address: "));
    WPRINT_APP_INFO(("%02X:%02X:%02X:%02X:%02X:%02X\r\n",
               mac.octet[0], mac.octet[1], mac.octet[2],
               mac.octet[3], mac.octet[4], mac.octet[5]));

    /* Start Queues */
    /* Used to push swipe values. They will be read by either the BLE or WiFi thread depending on which is active */
	wiced_rtos_init_queue(&swipe_queue_handle, "swipeQueue", SWIPE_MESSAGE_SIZE, SWIPE_QUEUE_SIZE);
    /* Used to accept OLED display messages. The messages are 1 byte command, 1 byte type, and 1 or 2 bytes data */
    wiced_rtos_init_queue(&display_queue_handle, "displayQueue", DISPLAY_MESSAGE_SIZE, DISPLAY_QUEUE_SIZE);

    /* Start Display and CapSense Threads */
	wiced_rtos_create_thread( &capsense_thread_handle,
							  CAPSENSE_PRIORITY,
							  "CapSense thread",
							  (wiced_thread_function_t) capSenseThread,
							  CAPSENSE_THREAD_STACK_SIZE,
							  NULL );
	wiced_rtos_create_thread( &display_thread_handle,
							  DISPLAY_PRIORITY,
							  "Display thread",
							  (wiced_thread_function_t) displayThread,
							  DISPLAY_THREAD_STACK_SIZE,
							  NULL );
}
