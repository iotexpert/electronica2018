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

/******************************************************
 *               Variable Definitions
 ******************************************************/
static uint16_t conn_id=0; /* Connection ID */

/* Water level % sent by the server */
static uint8_t waterLeft  = 0;
static uint8_t waterRight = 0;

static wiced_thread_t ble_swipe_thread_handle;

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
    uint8_t manuf_data[] = {0x31, 0x01, 0x2A}; /* Cypress Manuf ID in Little Endian format followed by code of 0x2A (42) */

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


void writeVal( uint16_t handle, void* pval, uint8_t len )
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

		WPRINT_APP_INFO(("wiced_bt_gatt_send_write 0x%X\r\n", status));
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

    switch( event )
    {
    case GATT_CONNECTION_STATUS_EVT:
        if ( p_data->connection_status.connected )
        {
        	WPRINT_APP_INFO(("Connected\r\n"));
            wiced_bt_gatt_connection_status_t *p_conn_status = &p_data->connection_status;
            conn_id         =  p_conn_status->conn_id;
            WPRINT_APP_INFO(("Connection ID=%d\r\n",conn_id));

            /* Stop advertisements */
        	wiced_bt_start_advertisements(BTM_BLE_ADVERT_OFF, 0, NULL);

        	/* Send Notify Message to Screen and enable notifications  */
        	displayCommand[DISPLAY_CMD] =  BLE_SCREEN;
			displayCommand[DISPLAY_TYPE] = REGISTER_NOTIFY;
			wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, WICED_NEVER_TIMEOUT);

			uint16_t cccdNotify = GATT_CLIENT_CONFIG_NOTIFICATION;
			writeVal(HDLD_CONTROLLER_WATERLEVELRIGHTBLE_CLIENT_CONFIGURATION, &cccdNotify, sizeof(GATT_CLIENT_CONFIG_NOTIFICATION));
			writeVal(HDLD_CONTROLLER_WATERLEVELLEFTBLE_CLIENT_CONFIGURATION,  &cccdNotify, sizeof(GATT_CLIENT_CONFIG_NOTIFICATION));

            /* Display message */
			wiced_rtos_delay_milliseconds(250); /* Wait before switching screens */
            displayCommand[DISPLAY_CMD] =  GAME_SCREEN;
            displayCommand[DISPLAY_TYPE] = INIT_BLE;
            wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, WICED_NEVER_TIMEOUT);
        }
        else
        {
        	WPRINT_APP_INFO(("Disconnected\r\n"));
            conn_id = 0;
            /* Restart advertising */
            wiced_bt_start_advertisements(BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL);
        }
        break;

    case GATT_OPERATION_CPLT_EVT:
        /* When you get something from the server, check to see if it is waterLevel data.
           If so, send it to the display for printing. */
    	WPRINT_APP_INFO(("Data Received Conn=%d Op=%d status=0x%X Handle=0x%X len=%d Data=%d\n",
                p_data->operation_complete.conn_id,
                p_data->operation_complete.op,
                p_data->operation_complete.status,
                p_data->operation_complete.response_data.handle,
                p_data->operation_complete.response_data.att_value.len,
				p_data->operation_complete.response_data.att_value.p_data[0]));

        if(p_data->operation_complete.response_data.handle == HDLC_CONTROLLER_WATERLEVELRIGHTBLE_VALUE)
        {
        	waterRight = p_data->operation_complete.response_data.att_value.p_data[0];
        }
        if(p_data->operation_complete.response_data.handle == HDLC_CONTROLLER_WATERLEVELLEFTBLE_VALUE)
		{
			waterRight = p_data->operation_complete.response_data.att_value.p_data[0];
		}
        /* Send value to display */
        displayCommand[DISPLAY_CMD] =  GAME_SCREEN;
        displayCommand[DISPLAY_TYPE] = WATER_VALUE;
        displayCommand[DISPLAY_VAL1] = waterLeft;
        displayCommand[DISPLAY_VAL2] = waterRight;
        wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, WICED_NEVER_TIMEOUT);
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
    wiced_bt_dev_ble_pairing_info_t *p_ble_info = NULL;
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

        	/* Set up BLE Screen */
            displayCommand[DISPLAY_CMD] =  BLE_SCREEN;
            displayCommand[DISPLAY_TYPE] = BLE_ADVERTISE;
            wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, WICED_NEVER_TIMEOUT);

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

    case BTM_PAIRING_IO_CAPABILITIES_BLE_REQUEST_EVT:
        /* Request for Pairing IO Capabilities (BLE) */
    	WPRINT_APP_INFO(("BLE Pairing IO Capabilities Request\r\n"));
        /* No IO Capabilities on this Platform */
        p_event_data->pairing_io_capabilities_ble_request.local_io_cap = BTM_IO_CAPABILITIES_NONE;
        p_event_data->pairing_io_capabilities_ble_request.oob_data = BTM_OOB_NONE;
        p_event_data->pairing_io_capabilities_ble_request.auth_req = BTM_LE_AUTH_REQ_BOND|BTM_LE_AUTH_REQ_MITM;
        p_event_data->pairing_io_capabilities_ble_request.max_key_size = 0x10;
        p_event_data->pairing_io_capabilities_ble_request.init_keys = 0;
        p_event_data->pairing_io_capabilities_ble_request.resp_keys = BTM_LE_KEY_PENC|BTM_LE_KEY_PID;
        break;

    case BTM_PAIRING_COMPLETE_EVT:
        /* Pairing is Complete */
        p_ble_info = &p_event_data->pairing_complete.pairing_complete_info.ble;
    	WPRINT_APP_INFO(("Pairing Complete %d.\r\n", p_ble_info->reason));
        break;

    case BTM_SECURITY_REQUEST_EVT:
        /* Security Request */
    	WPRINT_APP_INFO(("Security Request\r\n"));
        wiced_bt_ble_security_grant(p_event_data->security_request.bd_addr, WICED_BT_SUCCESS);
        break;

    case BTM_LOCAL_IDENTITY_KEYS_REQUEST_EVT:
    	WPRINT_APP_INFO(("Local Keys Request\r\n"));
    	status = WICED_BT_ERROR; /* No keys stored in NVRAM so indicate that there are no keys */
    	break;

    case BTM_LOCAL_IDENTITY_KEYS_UPDATE_EVT:
    	/* No keys stored in NVRAM so no need to do anything here */
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
			wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, WICED_NEVER_TIMEOUT);
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
    wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, WICED_NEVER_TIMEOUT);

    /* Start BLE stack - this starts 2 threads to manage BLE */
	wiced_bt_stack_init( ble_management_callback, &wiced_bt_cfg_settings, wiced_bt_cfg_buf_pools);
}
