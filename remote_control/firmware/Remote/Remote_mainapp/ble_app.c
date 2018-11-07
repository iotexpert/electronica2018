/*
Thread to handle BLE operations
 */

#include "global.h"
#include "wiced.h"
#include "wiced_bt_dev.h"
#include "wiced_bt_ble.h"
#include "wiced_bt_cfg.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_stack.h"
#include "ble_app.h"
#include "ble_db.h"
#include "capsense_app.h"
#include "display_app.h"

/******************************************************
 *                      Macros
 ******************************************************/
/* Thread parameters */
#define BLE_SWIPE_PRIORITY (7)
#define BLE_SWIPE_THREAD_STACK_SIZE (1*1024UL)

#define BLE_TIMEOUT 	500
#define CCCD_TIMER_TIME 500

/******************************************************
 *               Variable Definitions
 ******************************************************/
extern const wiced_bt_cfg_settings_t wiced_bt_cfg_settings;
extern wiced_bt_cfg_buf_pool_t wiced_bt_cfg_buf_pools[WICED_BT_CFG_NUM_BUF_POOLS];

static uint16_t conn_id=0; /* Connection ID */

/* Water level % sent by the server */
static uint8_t waterLeft  = 0;
static uint8_t waterRight = 0;

static wiced_thread_t ble_swipe_thread_handle;
static wiced_semaphore_t ble_semaphore_handle;

static int8_t displayCommand[DISPLAY_MESSAGE_SIZE] = {0}; /* Array to send messages to the display thread */

/******************************************************
 *                Function Definitions
 ******************************************************/
/* Set Advertisement Data */
void ble_adv_set_advertisement_data( void )
{
    wiced_result_t result;
	wiced_bt_ble_advert_elem_t adv_elem[3] = { 0 };
    uint8_t adv_flag = BTM_BLE_GENERAL_DISCOVERABLE_FLAG | BTM_BLE_BREDR_NOT_SUPPORTED;
    uint8_t num_elem = 0;
    uint8_t manuf_data[] = {0x31, 0x01, 'R', 'e', 'm', 'o', 't', 'e'}; /* Cypress Manuf ID in Little Endian format followed by a code */

    /* Advertisement Element for Flags */
    adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_FLAG;
    adv_elem[num_elem].len = sizeof(uint8_t);
    adv_elem[num_elem].p_data = &adv_flag;
    num_elem++;

    /* Advertisement Element for Name */
    adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_NAME_COMPLETE;
    adv_elem[num_elem].len = strlen((const char*)wiced_bt_cfg_settings.device_name);
    adv_elem[num_elem].p_data = wiced_bt_cfg_settings.device_name;
    num_elem++;

    /* Advertisement Element for Manufacturer data */
    adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_MANUFACTURER;
    adv_elem[num_elem].len = sizeof(manuf_data);
    adv_elem[num_elem].p_data = manuf_data;
    num_elem++;

    /* Set Raw Advertisement Data */
    result = wiced_bt_ble_set_raw_advertisement_data(num_elem, adv_elem);

    WPRINT_APP_INFO( ( "wiced_bt_ble_set_advertisement_data %d\n", result ) );
}


void writeVal( uint16_t handle, uint8_t* pval, uint8_t len )
{
	uint8_t buf[sizeof(wiced_bt_gatt_value_t) + len - 1];
	wiced_bt_gatt_value_t *p_write = ( wiced_bt_gatt_value_t* )buf;
	wiced_bt_gatt_status_t status;

	if(conn_id != 0) /* Don't try to send unless we have a connection */
	{
		memset(buf, 0, sizeof(buf));
			p_write->handle   = handle;
	        p_write->offset   = 0;
	        p_write->len      = len;
	        p_write->auth_req = GATT_AUTH_REQ_NONE;
	        memcpy(p_write->value, pval, len);

		status = wiced_bt_gatt_send_write ( conn_id, GATT_WRITE, p_write );

		WPRINT_APP_INFO(("wiced_bt_gatt_send_write status: 0x%02X, handle: 0x%02X, bytes: %d\r\n", status, p_write->handle, p_write->len));

		/* Wait for semaphore to make sure the write happened before continuing */
        wiced_rtos_get_semaphore(&ble_semaphore_handle, BLE_TIMEOUT);
	}
}


void bleSwipeThread( void )
{
	uint8_t queueMessage[SWIPE_MESSAGE_SIZE] = {0}; /* This is the message sent from the CapSense queue */

	while(1)
	{
		/* Wait for a new message in the queue */
		wiced_rtos_pop_from_queue(&swipe_queue_handle, &queueMessage, WICED_WAIT_FOREVER);

		if(queueMessage[0] == SWIPE_RIGHT)
		{
			writeVal(HDLC_CONTROLLER_PUMPRIGHTBLE_VALUE, &queueMessage[1], sizeof(queueMessage[1]));
		}
		else /* SWIPE_LEFT */
		{
			writeVal(HDLC_CONTROLLER_PUMPLEFTBLE_VALUE, &queueMessage[1], sizeof(queueMessage[1]));
		}
	}
}


wiced_bt_gatt_status_t gatt_callback( wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_data)
{
    wiced_bt_gatt_status_t result = WICED_BT_SUCCESS;
    wiced_bt_gatt_connection_status_t * p_conn_status = NULL;
	uint8_t cccdNotify[] = {GATT_CLIENT_CONFIG_NOTIFICATION & 0xff, (GATT_CLIENT_CONFIG_NOTIFICATION >> 8) & 0xff};
	static enum {WRITE_CCCD, GAME_ON} bleState;

    switch( event )
    {
    case GATT_CONNECTION_STATUS_EVT:
        if ( p_data->connection_status.connected )
        {
        	WPRINT_APP_INFO(("Connected\r\n"));
            p_conn_status = &p_data->connection_status;
            conn_id         =  p_conn_status->conn_id;
            WPRINT_APP_INFO(("Connection ID=%d\r\n",conn_id));

            /* Stop advertisements */
        	wiced_bt_start_advertisements(BTM_BLE_ADVERT_OFF, 0, NULL);

        	/* Send Notify Message to Screen */
        	displayCommand[DISPLAY_CMD] =  BLE_SCREEN;
			displayCommand[DISPLAY_TYPE] = REGISTER_NOTIFY;
			wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, BLE_TIMEOUT);

			/* Sign up for first notification. The second one will start in the gatt event complete callback */
			writeVal(HDLD_CONTROLLER_WATERLEVELLEFTBLE_CLIENT_CONFIGURATION,  cccdNotify, sizeof(cccdNotify));

        }
        else
        {
        	WPRINT_APP_INFO(("Disconnected\r\n"));
            conn_id = 0;	/* Reset connection ID */
            /* Restart timer to enable notifications for the next connection */
            wiced_bt_start_advertisements(BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL);	/* Restart advertising */

        }
        break;

    case GATT_OPERATION_CPLT_EVT:
        /* When you get something from the server, check to see if it is waterLevel data or CCCD write confirmation.
           If it is water data, send it to the display for printing. */
    	WPRINT_APP_INFO(("Data Received Conn=%d Op=%d status=0x%X Handle=0x%X len=%d Data=%d\n",
                p_data->operation_complete.conn_id,
                p_data->operation_complete.op,
                p_data->operation_complete.status,
                p_data->operation_complete.response_data.handle,
                p_data->operation_complete.response_data.att_value.len,
				p_data->operation_complete.response_data.att_value.p_data[0]));

    	/* Look for water level data */
        if(p_data->operation_complete.response_data.handle == HDLC_CONTROLLER_WATERLEVELLEFTBLE_VALUE)
		{
			waterLeft = p_data->operation_complete.response_data.att_value.p_data[0];
		}
        if(p_data->operation_complete.response_data.handle == HDLC_CONTROLLER_WATERLEVELRIGHTBLE_VALUE)
        {
        	waterRight = p_data->operation_complete.response_data.att_value.p_data[0];
        }

        /* State machine to sign up for notifications and switch game
         * screens the first time and then send water data after that.
         */
        switch(bleState)
        {
        case WRITE_CCCD:
			writeVal(HDLD_CONTROLLER_WATERLEVELRIGHTBLE_CLIENT_CONFIGURATION, cccdNotify, sizeof(cccdNotify));
			bleState = GAME_ON;
			/* Display game screen */
			displayCommand[DISPLAY_CMD] =  GAME_SCREEN;
			displayCommand[DISPLAY_TYPE] = INIT_BLE;
			wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, BLE_TIMEOUT);
        	break;
        case GAME_ON:
            displayCommand[DISPLAY_CMD] =  GAME_SCREEN;
            displayCommand[DISPLAY_TYPE] = WATER_VALUE;
			displayCommand[DISPLAY_VAL1] = waterLeft;
			displayCommand[DISPLAY_VAL2] = waterRight;
			wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, BLE_TIMEOUT);
        	break;
        }

        wiced_rtos_set_semaphore(&ble_semaphore_handle); /* This indicates to the writeVal function that the write is done */
        break;

    default:
    	WPRINT_APP_INFO(("Unknown GATT Event %d\r\n",event));
        break;
    }

    return result;
}


/* Bluetooth Management Event Handler */
wiced_bt_dev_status_t ble_management_callback( wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data )
{
    wiced_bt_dev_status_t status = WICED_BT_SUCCESS;
    wiced_bt_ble_advert_mode_t *p_adv_mode = NULL;
    wiced_bt_device_address_t bda;
    uint8_t i;

    switch (event)
    {
    case BTM_ENABLED_EVT:
        /* Bluetooth Controller and Host Stack Enabled */
    	WPRINT_APP_INFO(("Bluetooth Enabled (%s)\n",
                ((WICED_BT_SUCCESS == p_event_data->enabled.status) ? "success" : "failure")));

        if (WICED_BT_SUCCESS == p_event_data->enabled.status)
        {
        	/* Set BD_ADDR to the MAC address */
        	for(i = 0; i<BD_ADDR_LEN; i++)
        	{
        		bda[i] = mac.octet[i];
        	}
        	wiced_bt_set_local_bdaddr( bda );

        	/* Start a semaphore to control BLE write operations */
        	wiced_rtos_init_semaphore(&ble_semaphore_handle);

        	/* Set up BLE Screen */
            displayCommand[DISPLAY_CMD] =  BLE_SCREEN;
            displayCommand[DISPLAY_TYPE] = BLE_ADVERTISE;
            wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, BLE_TIMEOUT);

            /* Register callback function for GATT events */
            wiced_bt_gatt_register( gatt_callback );

        	/* Start Advertising */
            ble_adv_set_advertisement_data();
            wiced_bt_start_advertisements(BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL);

            /* Start thread to get messages from the swipe queue and push them to BLE */
			wiced_rtos_create_thread( &ble_swipe_thread_handle,
									  BLE_SWIPE_PRIORITY,
									  "BLW Swipe thread",
									  (wiced_thread_function_t) bleSwipeThread,
									  BLE_SWIPE_THREAD_STACK_SIZE,
									  NULL );
        }
        break;

    case BTM_LOCAL_IDENTITY_KEYS_UPDATE_EVT:
    	WPRINT_APP_INFO(("Local Keys Update\r\n"));
    	/* No keys stored in NVRAM so no need to do anything here */
    	break;

    case BTM_LOCAL_IDENTITY_KEYS_REQUEST_EVT:
    	WPRINT_APP_INFO(("Local Keys Request\r\n"));
    	status = WICED_BT_ERROR; /* No keys stored in NVRAM so indicate that there are no keys */
    	break;

    case BTM_BLE_ADVERT_STATE_CHANGED_EVT:
        /* Advertisement State Changed */
    	p_adv_mode = &p_event_data->ble_advert_state_changed;
    	WPRINT_APP_INFO(("Advertisement State Change: %d\n", *p_adv_mode));
        if(*p_adv_mode == BTM_BLE_ADVERT_UNDIRECTED_HIGH)
        {
        	/* Send Advertising Message to Screen */
        	displayCommand[DISPLAY_CMD] =  BLE_SCREEN;
			displayCommand[DISPLAY_TYPE] = BLE_CONNECT;
			wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, BLE_TIMEOUT);
        }
        break;

    case BTM_LPM_STATE_LOW_POWER:
    	/* No low power implementation */
    	break;

    default:
    	WPRINT_APP_INFO(("Unhandled Bluetooth Management Event: 0x%x (%d)\n", event, event));
        break;
    }
    return status;
}


void startBle( void )
{
	/* Set up BLE Screen */
    displayCommand[DISPLAY_CMD] =  BLE_SCREEN;
    displayCommand[DISPLAY_TYPE] = BLE_START;
    wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, BLE_TIMEOUT);

    /* Start BLE stack - this starts 2 threads to manage BLE */
	wiced_bt_stack_init( ble_management_callback, &wiced_bt_cfg_settings, wiced_bt_cfg_buf_pools);
}
