#include "wiced.h"
#include "bt.h"

extern uint8_t g_hello_client_cnt;

extern uint8_t leftLevel;
extern uint8_t rightLevel;

static BT_STATE_T btState = BT_UNINITIALIZED;
extern void startBLE(void);


wiced_result_t bt_start(void)
{
	startBLE();
	wiced_result_t ret = WICED_SUCCESS;
    return ret;
}

void btThread(wiced_thread_arg_t arg)
{
    static uint8_t previousLeftLevel = 255;         //set outside normal range 255 so it will trigger update on first connected iteration
    static uint8_t previousRightLevel = 255;         //set outside normal range 255 so it will trigger update on first connected iteration

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
				if(g_hello_client_cnt)
				{
					//kmwh
					//update BLE water levels
					//have to check each connected device for subscription
					//and then publish water levels if subscribed
					if((previousLeftLevel != leftLevel) || (previousRightLevel != rightLevel))
					{
						previousLeftLevel = leftLevel;
						previousRightLevel = rightLevel;
					}

				}
				break;

			case BT_ERROR:
			default:
				//try and gracefully recover from bad state or error
				break;
		}
		wiced_rtos_delay_milliseconds(BT_THREAD_DELAY);
	}
}
