/* Electronic game remote OLED Display and Button LEDs */

#include "global.h"
#include "wiced.h"
#include "cy_pdl.h"
#include "cy_syslib.h"
#include "cycfg.h"
#include "u8g2.h"
#include "display_app.h"

/******************************************************
 *                      Macros
 ******************************************************/
/* Blinking LED timer time */
#define TIMER_TIME (200)
/* I2C Timeout in ms */
#define TIMEOUT 1000

/******************************************************
 *               Variable Definitions
 ******************************************************/
cy_stc_scb_i2c_context_t I2C_context;

const cy_stc_sysint_t I2C_SCB_IRQ_cfg = {
    .intrSrc = scb_3_interrupt_IRQn,
    .intrPriority = 7u
};

u8x8_t u8x8; /* Display structure */

/* RTOS structures */
static wiced_timer_t  ble_led_timer_handle;
static wiced_timer_t  wifi_led_timer_handle;
wiced_queue_t	      display_queue_handle;

char msg[20];   /* Array to hold snprintf output for display */

/*******************************************************************************
* Function Definitions
*******************************************************************************/
static void I2C_Interrupt(void)
{
    Cy_SCB_I2C_Interrupt(I2C_HW, &I2C_context);
}


void BleLedTimer(void* arg)
{
	Cy_GPIO_Inv(BT_LED_PORT,   BT_LED_NUM);
}


void WifiLedTimer(void* arg)
{
	Cy_GPIO_Inv(WIFI_LED_PORT, WIFI_LED_NUM);
}


/*******************************************************************************
* Function Name: uint8_t u8x8_byte_hw_i2c( u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr )
********************************************************************************
*
* Summary:
*  This is a hardware abstraction layer for the u8x8 library
*
*  Return: Status - Return 1 for a valid case, 0 for an invalid case
*
*  Inputs:
*     *u8x8:    Pointer to a OLED structure
*     msg:      The type of I2C message to send (start, send bytes, or stop))
*     arg_int:  The number of bytes to send
*     *arg_ptr: Pointer to the bytes to send
*
*  Note: No error checking is done on the I2C transactions
********************************************************************************/
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    uint8_t *data;
    switch(msg)
    {
        case U8X8_MSG_BYTE_SEND:    // Send arg_int bytes from arg_ptr
            data = (uint8_t *)arg_ptr;
            while( arg_int > 0 )
            {
                (void) Cy_SCB_I2C_MasterWriteByte(I2C_HW, *data, TIMEOUT, &I2C_context);
  	            data++;
	            arg_int--;
            }
            break;
        case U8X8_MSG_BYTE_INIT: // Using the HW block so you dont need to initialize
            break;
        case U8X8_MSG_BYTE_SET_DC:
            break;
        case U8X8_MSG_BYTE_START_TRANSFER: // Send an I2C start
            (void) Cy_SCB_I2C_MasterSendStart(I2C_HW, u8x8_GetI2CAddress(u8x8)>>1, CY_SCB_I2C_WRITE_XFER, TIMEOUT, &I2C_context);
            break;
        case U8X8_MSG_BYTE_END_TRANSFER:   // Send an I2C stop
            (void) Cy_SCB_I2C_MasterSendStop(I2C_HW, TIMEOUT, &I2C_context);
            break;
        default:
            return 0;
    }
    return 1;
}

/*******************************************************************************
* Function Name: uint8_t psoc_gpio_and_delay_cb( u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr )
********************************************************************************
*
* Summary:
*  This is a callback function used by the u8x8 library. It is used to add
*  a delay using the avaialable PSoC delay functions.
*
*  The delay can be a specified number of milliseconds, 10 microseconds, or 100 nanoseconds
*
*  Return: Status - Return 1 for a valid case, 0 for an invalid case
*
*  Inputs:
*     *u8x8:    Unused but requierd since the u8x8 library call provides it
*     msg:      The type of delay (x milliseconds, 10 microseconds, or 100 nanoseconds)
*     arg_int:  The delay in millisconds (for the mmillisecond delay type)
*     *arg_ptr: Unused but requierd since the u8x8 library call provides it
********************************************************************************/
uint8_t psoc_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    (void)u8x8;
    (void)arg_ptr;
    switch(msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: // No initialization required
            break;
        case U8X8_MSG_DELAY_MILLI:
            CyDelay(arg_int);
            break;
        case U8X8_MSG_DELAY_10MICRO:
            CyDelayUs(10);
         break;
        case U8X8_MSG_DELAY_100NANO:
            CyDelayUs(1);
            break;
        /* We only use I2C in HW so nont of these cases are used
         * If you want to use a software interface or have these pins then you
         * need to read and write them */
        case U8X8_MSG_GPIO_SPI_CLOCK:
        case U8X8_MSG_GPIO_SPI_DATA:
        case U8X8_MSG_GPIO_CS:
        case U8X8_MSG_GPIO_DC:
        case U8X8_MSG_GPIO_RESET:
        //case U8X8_MSG_GPIO_D0: // Same as SPI_CLOCK
        //case U8X8_MSG_GPIO_D1: // Same as SPI_DATA
        case U8X8_MSG_GPIO_D2:
        case U8X8_MSG_GPIO_D3:
        case U8X8_MSG_GPIO_D4:
        case U8X8_MSG_GPIO_D5:
        case U8X8_MSG_GPIO_D6:
        case U8X8_MSG_GPIO_D7:
        case U8X8_MSG_GPIO_E:
        case U8X8_MSG_GPIO_I2C_CLOCK:
        case U8X8_MSG_GPIO_I2C_DATA:
            break;
        default:
            return 0;
    }
    return 1;
}


void drawSplash( void )
{
	u8x8_ClearDisplay(&u8x8);
	snprintf(msg, sizeof(msg), " Cypress");
	u8x8_DrawString(&u8x8,3,0,msg);
	snprintf(msg, sizeof(msg), " Choose");
	u8x8_DrawString(&u8x8,3,2,msg);
	snprintf(msg, sizeof(msg), "Bluetooth");
	u8x8_DrawString(&u8x8,3,3,msg);
	snprintf(msg, sizeof(msg), " or WiFi");
	u8x8_DrawString(&u8x8,3,4,msg);
}


void drawBle( int8_t type )
{
	switch (type)
	{
	case BLE_START:
	    wiced_rtos_stop_timer(&wifi_led_timer_handle);
		Cy_GPIO_Write(WIFI_LED_PORT, WIFI_LED_NUM, LED_OFF);
	    u8x8_ClearDisplay(&u8x8);
		snprintf(msg, sizeof(msg), "Start BLE");
		u8x8_DrawString(&u8x8,3,0,msg);
		break;
	case BLE_ADVERTISE:
		snprintf(msg, sizeof(msg), "Start Advertise");
		u8x8_DrawString(&u8x8,0,1,msg);
		break;
	case BLE_CONNECT:
		snprintf(msg, sizeof(msg), "Wait For Connect");
		u8x8_DrawString(&u8x8,0,2,msg);
		break;
	case REGISTER_NOTIFY:
		snprintf(msg, sizeof(msg), "Register Notify");
		u8x8_DrawString(&u8x8,0,3,msg);
		break;
	}
}


void drawWiFi( int8_t type )
{
	switch (type)
	{
	case WIFI_CONNECT:
	    wiced_rtos_stop_timer(&ble_led_timer_handle);
		Cy_GPIO_Write(BT_LED_PORT, BT_LED_NUM, LED_OFF);
	    u8x8_ClearDisplay(&u8x8);
		snprintf(msg, sizeof(msg), "Connecting WiFi");
		u8x8_DrawString(&u8x8,0,0,msg);

		break;
	case AWS_RESOURCES:
		snprintf(msg, sizeof(msg), "Loading Resources");
		u8x8_DrawString(&u8x8,0,1,msg);
		break;
	case AWS_CONNECT:
		snprintf(msg, sizeof(msg), "Connecting AWS");
		u8x8_DrawString(&u8x8,0,2,msg);
		break;
	case SUBSCRIBE_SHADOW:
		snprintf(msg, sizeof(msg), "Subscribing");
		u8x8_DrawString(&u8x8,0,3,msg);
		break;
	}
}


void drawGame( int8_t* message )
{
	switch(message[DISPLAY_TYPE])
	{
	case INIT_BLE:
	case INIT_WIFI:
		u8x8_ClearDisplay(&u8x8);
		snprintf(msg, sizeof(msg), "Game On!");
		u8x8_DrawString(&u8x8,3,0,msg);
		snprintf(msg, sizeof(msg), "Water Level");
		u8x8_DrawString(&u8x8,2,3,msg);
		if(message[DISPLAY_TYPE] == INIT_BLE)
		{
			wiced_rtos_stop_timer(&ble_led_timer_handle);
			Cy_GPIO_Write(BT_LED_PORT, BT_LED_NUM, LED_ON);
		}
		else /* INIT_WIFI */
		{
			wiced_rtos_stop_timer(&wifi_led_timer_handle);
			Cy_GPIO_Write(WIFI_LED_PORT, WIFI_LED_NUM, LED_ON);
		}
		break;
	case WATER_VALUE:
		snprintf(msg, sizeof(msg), "L: %3d   R: %3d",message[DISPLAY_VAL1], message[DISPLAY_VAL2]);
		u8x8_DrawString(&u8x8,0,4,msg);
		break;
	}
}


void drawSwipe( int8_t* message )
{
	snprintf(msg, sizeof(msg), "Swipe: %4d", message[DISPLAY_VAL1]);
	u8x8_DrawString(&u8x8,2,6,msg);
}


void displayThread( void )
{
	int8_t displayMessage[DISPLAY_MESSAGE_SIZE] = {0};

	/* Initialize Button LEDs */
	Cy_GPIO_Pin_Init(BT_LED_PORT, BT_LED_PIN, &BT_LED_config);
	Cy_GPIO_Pin_Init(WIFI_LED_PORT, WIFI_LED_PIN, &WIFI_LED_config);

	/* Initialize timers to toggle Button LEDs until a connection is established */
	wiced_rtos_init_timer(&ble_led_timer_handle,  TIMER_TIME, BleLedTimer,  NULL);
	wiced_rtos_init_timer(&wifi_led_timer_handle, TIMER_TIME, WifiLedTimer, NULL);
    wiced_rtos_start_timer(&ble_led_timer_handle);
    wiced_rtos_start_timer(&wifi_led_timer_handle);

	/* Initialize and enable the I2C in master mode. */
    Cy_SCB_I2C_Init(I2C_HW, &I2C_config, &I2C_context);
    Cy_SysInt_Init(&I2C_SCB_IRQ_cfg, &I2C_Interrupt);  /* Hook interrupt service routine. */
    NVIC_EnableIRQ((IRQn_Type) I2C_SCB_IRQ_cfg.intrSrc); /* Enable interrupt in NVIC. */
    Cy_SCB_I2C_Enable(I2C_HW); /* Enable I2C master hardware. */

    /* Initialize the U8 Display */
    //GJL pick a font size - need to wrap fonts in #ifdef?
    u8x8_Setup(&u8x8, u8x8_d_ssd1306_128x64_noname, u8x8_cad_ssd13xx_i2c, u8x8_byte_hw_i2c, psoc_gpio_and_delay_cb);
    u8x8_InitDisplay(&u8x8);
    u8x8_SetPowerSave(&u8x8,0);
    u8x8_SetFont(&u8x8,u8x8_font_amstrad_cpc_extended_f);

    drawSplash();

    /* Start queue to accept messages. The messages are 1 byte command, 1 byte type, and 1 or 2 bytes data */
    wiced_rtos_init_queue(&display_queue_handle, "displayQueue", DISPLAY_MESSAGE_SIZE, DISPLAY_QUEUE_SIZE);

    while(1)
    {
    	/* Wait for a new display command */
    	wiced_rtos_pop_from_queue(&display_queue_handle, &displayMessage, WICED_NEVER_TIMEOUT);

    	switch (displayMessage[DISPLAY_CMD])
    	{
    	case BLE_SCREEN:
    		drawBle(displayMessage[DISPLAY_TYPE]);
    		break;
    	case WIFI_SCREEN:
    		drawWiFi(displayMessage[DISPLAY_TYPE]);
    		break;
    	case GAME_SCREEN:
    		drawGame(displayMessage);
    		break;
    	case SWIPE_VALUE:
    		drawSwipe(displayMessage);
    		break;
    	}

    } /* End of while(1) */
}

