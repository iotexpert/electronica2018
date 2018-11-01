/*
 Electronica 2018 Game Remote
 */
#include "wiced.h"
#include "global.h"
#include "cy_capsense.h"
#include "cy_pdl.h"
#include "cy_syslib.h"
#include "cycfg.h"
#include "cycfg_capsense.h"
#include "aws_app.h"

/******************************************************
 *                      Macros
 ******************************************************/
/* Thread parameters */
#define AWS_PRIORITY (4)
#define AWS_THREAD_STACK_SIZE (5*1024UL)
#define BLE_PRIORITY (4)
#define BLE_THREAD_STACK_SIZE (5*1024UL)

/* Constants for the queue to pass swipe messages. 1st 2 bytes are direction, last 2 bytes are value */
#define MESSAGE_SIZE		(4)
#define QUEUE_SIZE			(100)

/* Blinking LED timer time */
#define TIMER_TIME (200)

/* Used for the mode */
#define INIT (0)
#define BLE  (2)
#define WIFI (1)

/* LED states - LEDs are active low */
#define LED_OFF (1)
#define LED_ON  (0)

/******************************************************
 *               Variable Definitions
 ******************************************************/
wiced_bool_t state = 	 	INITSTATE;		//Current state of the remote
wiced_bool_t nextState = 	INITSTATE;		//Desired state of the remote - set by BLE and AWS threads

wiced_mac_t mac; 	/* Device MAC address */

/* RTOS structures */
static wiced_thread_t aws_thread_handle;
static wiced_thread_t ble_thread_handle;
static wiced_timer_t  ledtimer_handle;
wiced_queue_t  swipe_queue_handle;

/*******************************************************************************
* CapSense Interrupt configuration
*******************************************************************************/
const cy_stc_sysint_t CapSense_ISR_cfg =
{
    .intrSrc = csd_interrupt_IRQn,
    .intrPriority = 6u,
};

/*******************************************************************************
* Function Definitions
*******************************************************************************/
void platform_csd_irq(void)
{
    Cy_CapSense_InterruptHandler(CSD0, &cy_capsense_context);
}


void ledBlink(void* arg)
{
	static uint8_t ledState = LED_ON;
	if(*(uint8_t*)arg == INIT)
	{
		Cy_GPIO_Write(BT_LED_PORT,   BT_LED_NUM, ledState);
		Cy_GPIO_Write(WIFI_LED_PORT, WIFI_LED_NUM, ledState);
	}
	else if (*(uint8_t*)arg == BLE)
	{
		Cy_GPIO_Write(BT_LED_PORT,   BT_LED_NUM, ledState);
	}
	else
	{
		Cy_GPIO_Write(WIFI_LED_PORT, WIFI_LED_NUM, ledState);
	}
	ledState = !ledState;
}


void application_start( void )
{
    wiced_init( );

    uint8_t mode = INIT;

    /* Variables for slider swipe calculations */
	uint16_t startCoord  = 		0u;
	uint16_t endCoord = 		0u;
	uint16_t coord;
	int16_t swipe;
	cy_stc_capsense_touch_t *sldrTouch;
	wiced_bool_t activeTouch = WICED_FALSE;
	uint16_t swipeMessage[2];

	/* Initialize LEDs */
	Cy_GPIO_Pin_Init(BT_LED_PORT, BT_LED_PIN, &BT_LED_config);
	Cy_GPIO_Pin_Init(WIFI_LED_PORT, WIFI_LED_PIN, &WIFI_LED_config);
	Cy_GPIO_Pin_Init(SLD_LED_PORT, SLD_LED_PIN, &SLD_LED_config);

	//GJL Make CapSense a thread and use the callback function
	/* Initialize/Enable CapSense and CapSense Interrupt */
	Cy_CapSense_Init(&cy_capsense_context);
	Cy_SysInt_Init(&CapSense_ISR_cfg, &platform_csd_irq);
	NVIC_ClearPendingIRQ(CapSense_ISR_cfg.intrSrc);
	NVIC_EnableIRQ(CapSense_ISR_cfg.intrSrc);
	Cy_CapSense_Enable(&cy_capsense_context);
	/* Start CapSense block - Initializes CapSense Data structure and performs first scan to set up sensor baselines */
	Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

	/* Timer to toggle an LED while a connection is being established.
	 * Mode is used to determine which LED to blink.
	 * Before a button is pressed, both LEDs will blink. */
    wiced_rtos_init_timer(&ledtimer_handle, TIMER_TIME, ledBlink, &mode);
    wiced_rtos_start_timer(&ledtimer_handle);

    /* Queue will be used to push swipe values. They will be read by either the BLE or WiFi thread depending on which is active */
	wiced_rtos_init_queue(&swipe_queue_handle, "swipeQueue", MESSAGE_SIZE, QUEUE_SIZE);

	/* Get device MAC Address to be used as thing name or Bluetooth device address */
    wiced_wifi_get_mac_address(&mac);
    WPRINT_APP_INFO(("MAC Address: "));
    WPRINT_APP_INFO(("%02X:%02X:%02X:%02X:%02X:%02X\r\n",
               mac.octet[0], mac.octet[1], mac.octet[2],
               mac.octet[3], mac.octet[4], mac.octet[5]));

	while(1)
	{
		/* Handle CapSense */
		if(CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(&cy_capsense_context))
		{
			/* Process all widgets */
			Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);

			if(state == INITSTATE) // Only look at buttons until a connection is requested
			{
				if(Cy_CapSense_IsWidgetActive(CY_CAPSENSE_BTBTN_WDGT_ID, &cy_capsense_context)) /* Bluetooth Button */
				{
					WPRINT_APP_INFO(("Connecting to BLE\n"));
					state = CONNECTING;
					mode = BLE;
					Cy_GPIO_Write(WIFI_LED_PORT, WIFI_LED_NUM, LED_OFF); /* Turn off WIFI LED */
					/* Start up Bluetooth thread */
					wiced_rtos_create_thread( &ble_thread_handle,
											  BLE_PRIORITY,
											  "BLE thread",
											  (wiced_thread_function_t) awsThread, //GJL TEMP
											  BLE_THREAD_STACK_SIZE,
											  NULL );
				}
				else if(Cy_CapSense_IsWidgetActive(CY_CAPSENSE_WIFIBTN_WDGT_ID, &cy_capsense_context)) /* WiFi Button */
				{
					WPRINT_APP_INFO(("Connecting to WIFI\n"));
					state = CONNECTING;
					mode = WIFI;
					Cy_GPIO_Write(BT_LED_PORT, BT_LED_NUM, LED_OFF); /* Turn off BT LED */
					/* Start up AWS thread */
					wiced_rtos_create_thread( &aws_thread_handle,
											  AWS_PRIORITY,
											  "AWS thread",
											  (wiced_thread_function_t) awsThread,
											  AWS_THREAD_STACK_SIZE,
											  NULL );
				}
			} // end if state is INITIALSTATE

			if(state == CONNECTED)  // Only look at slider once a connection has been established
			{
				/* Slider */
				if(Cy_CapSense_IsWidgetActive(CY_CAPSENSE_SLIDER_WDGT_ID, &cy_capsense_context))
				{
					Cy_GPIO_Write(WIFI_LED_PORT, SLD_LED_NUM, LED_ON);
					sldrTouch = Cy_CapSense_GetTouchInfo(CY_CAPSENSE_SLIDER_WDGT_ID, &cy_capsense_context);
					coord = sldrTouch->ptrPosition->x;
					if(WICED_FALSE == activeTouch)
					{
						activeTouch = WICED_TRUE;
						startCoord = coord;
					}
					else // This is not the starting coordinate but it might be the end coordinate
					{
						endCoord = coord;
					}
				}
				else // Slider is not being touched
				{
					Cy_GPIO_Write(WIFI_LED_PORT, SLD_LED_NUM, LED_OFF);
					if(WICED_TRUE == activeTouch)  /* This is the lift off event - need to send the swipe value */
					{
		                  swipe = (int16_t)endCoord - (int16_t)startCoord;
		                  activeTouch = WICED_FALSE;
		                  startCoord = 0;
		                  endCoord = 0;
		                  if(swipe > 0) /* Swipe Right */
		                  {
		                	  swipeMessage[0] = RIGHT;
			                  WPRINT_APP_INFO(("Right Swipe: %d\n", swipe));
		                  }
		                  else /* Swipe Left */
		                  {
		                	  swipeMessage[0] = LEFT;
		                	  swipe = -swipe;
			                  WPRINT_APP_INFO(("Left Swipe: %d\n", swipe));
		                  }
		                  swipeMessage[1] = swipe;
		                  wiced_rtos_push_to_queue(&swipe_queue_handle, &swipeMessage, WICED_NO_WAIT);
					}
				}
			}
			Cy_CapSense_ScanAllWidgets(&cy_capsense_context); // Start the next scan
		} // end if CapSense not busy


		/* Stop blinking the connection LED and turn it on once the connection is made */
		if(state != CONNECTED && nextState == CONNECTED)
		{
			state = CONNECTED;
			wiced_rtos_stop_timer(&ledtimer_handle);
			if(mode == BLE)
			{
				Cy_GPIO_Write(BT_LED_PORT,   BT_LED_NUM,   LED_ON);
			}
			else
			{
				Cy_GPIO_Write(WIFI_LED_PORT, WIFI_LED_NUM, LED_ON);
			}
		}

		wiced_rtos_delay_milliseconds(1);
	}
}
