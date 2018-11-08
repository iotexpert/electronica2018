/*
 * BLE functionality
 */

#include "wiced.h"
#include "wiced_bt_dev.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_cfg.h"
#include "wiced_bt_stack.h"
#include "ble_db.h"
#include "ble_app.h"

/* Timer timeout */
#define TIMEOUT_IN_MS          (100)
#define MESSAGE_SIZE        (4)
#define QUEUE_SIZE          (10)

uint8_t leftLevel = 0;
uint8_t rightLevel = 0;

wiced_queue_t pumpRequestQueueHandle;

wiced_timer_t test_timer_handle;

void testTimer( void* arg )
{
    static uint8_t count = 0;

    count++;

    if(count % 2 == 0)
    {
        leftLevel++;
        if (leftLevel > 90)
        {
            leftLevel = 1;
        }
    }
    else
    {
        rightLevel += 2;
        if (rightLevel > 95)
        {
            rightLevel = 0;
        }
    }
}

void application_start( void )
{
    wiced_init();

    wiced_rtos_init_queue(&pumpRequestQueueHandle, "pumpRequestQueue", MESSAGE_SIZE, QUEUE_SIZE); /* Setup the queue for pump run requests  */

    startBle();

    //GJL timer to test water levels
     wiced_rtos_init_timer(&test_timer_handle, 2000, testTimer, NULL);
     wiced_rtos_start_timer(&test_timer_handle);
}
