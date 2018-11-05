/* Electronica 2018 Game Remote CapSense*/
#include "global.h"
#include "wiced.h"
#include "cy_capsense.h"
#include "cy_pdl.h"
#include "cy_syslib.h"
#include "cycfg.h"
#include "cycfg_capsense.h"
#include "ble_app.h"
#include "aws_app.h"
#include "capsense_app.h"
#include "display_app.h"

/* Thread parameters */
#define AWS_PRIORITY (5)
#define AWS_THREAD_STACK_SIZE (5*1024UL)
#define BLE_PRIORITY (5)
#define BLE_THREAD_STACK_SIZE (25*1024UL)

/******************************************************
 *               Variable Definitions
 ******************************************************/
/* RTOS structures */
static wiced_thread_t aws_thread_handle;
static wiced_thread_t ble_thread_handle;
static wiced_semaphore_t capsense_semaphore_handle;

wiced_queue_t  swipe_queue_handle;

/* Array to send messages to the display thread */
static int8_t displayCommand[DISPLAY_MESSAGE_SIZE] = {0};

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

void capSenseCallback(cy_stc_active_scan_sns_t * ptrActiveScan)
{
	wiced_rtos_set_semaphore(&capsense_semaphore_handle);
}

void capSenseThread( void )
{
	/* Variables for slider swipe calculations */
	uint16_t startCoord  = 		0u;
	uint16_t endCoord = 		0u;
	uint16_t coord;
	int16_t swipe;
	cy_stc_capsense_touch_t *sldrTouch;
	wiced_bool_t activeTouch = WICED_FALSE;
	uint8_t swipeMessage[SWIPE_MESSAGE_SIZE] = {0};

	wiced_bool_t initialTouch = WICED_FALSE; /* Keeps track of whether a button has been pressed yet */

	/* Initialize Slider LED */
	Cy_GPIO_Pin_Init(SLD_LED_PORT, SLD_LED_PIN, &SLD_LED_config);

	/* Semaphore is used to alert the thread when a scan is done */
	wiced_rtos_init_semaphore(&capsense_semaphore_handle);
    /* Queue will be used to push swipe values. They will be read by either the BLE or WiFi thread depending on which is active */
	wiced_rtos_init_queue(&swipe_queue_handle, "swipeQueue", SWIPE_MESSAGE_SIZE, SWIPE_QUEUE_SIZE);

	/* Initialize/Enable CapSense and CapSense Interrupt */
	Cy_CapSense_Init(&cy_capsense_context);
	Cy_SysInt_Init(&CapSense_ISR_cfg, &platform_csd_irq);
	NVIC_ClearPendingIRQ(CapSense_ISR_cfg.intrSrc);
	NVIC_EnableIRQ(CapSense_ISR_cfg.intrSrc);
	Cy_CapSense_RegisterCallback(CY_CAPSENSE_END_OF_SCAN_E, capSenseCallback, &cy_capsense_context);
	Cy_CapSense_Enable(&cy_capsense_context);
	/* Start CapSense block - Initializes CapSense Data structure and performs first scan to set up sensor baselines */
	Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

	while(1)
	{
		/* Wait for CapSense scan to be done - this is set in the callback */
		wiced_rtos_get_semaphore(&capsense_semaphore_handle, WICED_WAIT_FOREVER);

		/* Process all widgets */
		Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);

		if(WICED_FALSE == initialTouch) // Only look at buttons until a connection is requested
		{
			if(Cy_CapSense_IsWidgetActive(CY_CAPSENSE_BTBTN_WDGT_ID, &cy_capsense_context)) /* Bluetooth Button */
			{
				WPRINT_APP_INFO(("Connecting to BLE\n"));
				initialTouch = WICED_TRUE;
				/* Start up Bluetooth thread */
				wiced_rtos_create_thread( &ble_thread_handle,
										  BLE_PRIORITY,
										  "BLE thread",
										  (wiced_thread_function_t) bleThread,
										  BLE_THREAD_STACK_SIZE,
										  NULL );
			}
			else if(Cy_CapSense_IsWidgetActive(CY_CAPSENSE_WIFIBTN_WDGT_ID, &cy_capsense_context)) /* WiFi Button */
			{
				WPRINT_APP_INFO(("Connecting to WIFI\n"));
				initialTouch = WICED_TRUE;
				/* Start up AWS thread */
				wiced_rtos_create_thread( &aws_thread_handle,
										  AWS_PRIORITY,
										  "AWS thread",
										  (wiced_thread_function_t) awsThread,
										  AWS_THREAD_STACK_SIZE,
										  NULL );
			}
		} /* end if initialTouch FALSE */

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
		else /* Slider is not being touched */
		{
			Cy_GPIO_Write(SLD_LED_PORT, SLD_LED_NUM, LED_OFF);
			if(WICED_TRUE == activeTouch)  /* This is the lift off event - need to send the swipe value */
			{
				  swipe = (int16_t)endCoord - (int16_t)startCoord;
				  /* Prevent swipes of 100 to make it more challenging to send a big value */
				  if(swipe == 100)
				  {
					  swipe = 50;
				  }
				  if(swipe == -100)
				  {
					  swipe = -50;
				  }
				  /* Display swipe message on screen */
				  displayCommand[DISPLAY_CMD] =  SWIPE_VALUE;
				  displayCommand[DISPLAY_VAL1] = (int8_t)swipe;
				  wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, WICED_NEVER_TIMEOUT);
				  if(swipe > 0) /* Swipe Right */
				  {
					  swipeMessage[0] = SWIPE_RIGHT;
					  WPRINT_APP_INFO(("Right Swipe: %d\n", swipe));
				  }
				  else /* Swipe Left */
				  {
					  swipeMessage[0] = SWIPE_LEFT;
					  swipe = -swipe;
					  WPRINT_APP_INFO(("Left Swipe: %d\n", swipe));
				  }
				  swipeMessage[1] = swipe;
				  wiced_rtos_push_to_queue(&swipe_queue_handle, &swipeMessage, WICED_NO_WAIT);
				  /* Reset for next swipe */
				  activeTouch = WICED_FALSE;
				  startCoord = 0;
				  endCoord = 0;
			} /* End of lift off event */
		} /* End of slider not being touched */
		Cy_CapSense_ScanAllWidgets(&cy_capsense_context); // Start the next scan
	} /* End of while(1) */
}
