#include "wiced.h"
#include "bt.h"

static BT_STATE_T btState = BT_UNINITIALIZED;


wiced_result_t bt_start(void)
{
	wiced_result_t ret = WICED_SUCCESS;
    return ret;
}

void btThread(wiced_thread_arg_t arg)
{
    uint8_t threadTicks = 0;

    while(1)
	{
		switch(btState)
		{
			case BT_UNINITIALIZED:
                WPRINT_APP_INFO(("Starting BT - \n"));
                if(bt_start() == WICED_SUCCESS)
                {
                    btState = BT_INITIALIZED;
                    WPRINT_APP_INFO(("BT started - \n"));
                }
				break;

			case BT_INITIALIZED:
				break;

			case BT_ERROR:
			default:
				//try and gracefully recover from bad state or error
				break;
		}
		wiced_rtos_delay_milliseconds(BT_THREAD_DELAY);
        threadTicks++;
	}
}
