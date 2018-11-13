/*
 * BLE functionality
 */

#include "wiced.h"
#include "wiced_bt_dev.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_cfg.h"
#include "wiced_bt_stack.h"
#include "ble_db.h"
#include "pumps.h"
#include "liquidlevel.h"
#include "globals.h"

/******************************************************************************
 *                          Macros
 ******************************************************************************/
/* Max number of allowed BLE connections */
/* May also need to change the wiced_bt_cfg.c file values - currently they are set at 4 */
#define REMOTE_MAX 2

/* Timer timeout */
#define TIMEOUT_IN_MS          (100)

/******************************************************************************
 *                          Type  Definitions
 ******************************************************************************/
/* Structure to hold connected Remote info */
typedef struct
{
	uint16_t conn_id;                   // Connection Identifier
	uint8_t  remote_addr[BD_ADDR_LEN];  // Remote BD Address
	uint16_t cccdWaterLeft;             // CCCD value for left water level (notifications)
	uint16_t cccdWaterRight;            // CCCD value for left water level (notifications)
} remote_info_t;

/******************************************************************************
 *                          Variables Definitions
 ******************************************************************************/
remote_info_t   remote_info[REMOTE_MAX];  /* Hold info for up to 2 remotes */
uint8_t         remote_cnt=0;    /* Keep track of the number of remotes connected */

static wiced_timer_t notify_timer_handle; /* Thread to manage notifications */

extern const wiced_bt_cfg_settings_t wiced_bt_cfg_settings;
extern const wiced_bt_cfg_buf_pool_t wiced_bt_cfg_buf_pools[];

/* GJL: add variable to allow enable/disable of scanning from command console and during a game */
wiced_bool_t enableBleScanning = WICED_TRUE;

/******************************************************************************
 *                          Function Definitions
 ******************************************************************************/
/* This function adds the remote information to the structure on a new connection */
static void game_add_remote_info( uint16_t conn_id, uint8_t* p_bd_addr )
{
	uint8_t i;

	if ( remote_cnt < REMOTE_MAX )      /* Check to make sure we have space for a new remote */
	{
		for(i=0; i < REMOTE_MAX; i++)   /* Find the first open slot */
		{
			if (remote_info[i].conn_id == 0)
			{
				remote_info[remote_cnt].conn_id = conn_id;
				memcpy( remote_info[remote_cnt].remote_addr, p_bd_addr, BD_ADDR_LEN );
				remote_info[remote_cnt].cccdWaterLeft =  0x0000; /* Start with notifications off */
				remote_info[remote_cnt].cccdWaterRight = 0x0000; /* Start with notifications off */
				remote_cnt++; /* Increment number of connected remotes */
				break; /* Exit out of the for loop now that we added the device */
			}
		}
	}
}

/* This function removes the remote information from the structure when a connection is lost */
static void game_remove_remote_info( uint16_t conn_id )
{
	uint8_t i;

	for(i=0; i < REMOTE_MAX; i++)   /* Find the matching remote */
	{
		if(remote_info[i].conn_id == conn_id)
		{
			remote_info[i].conn_id = 0;
			if(remote_cnt > 0)
			{
				remote_cnt--; /* Reduce number of connected remotes */
			}
		}
	}
}


/* This function searches for the remote specified by a conn_id and returns the index in the array of structures */
static uint8_t game_get_remote_info( uint16_t conn_id )
{
	uint8_t i;

	for(i=0; i < REMOTE_MAX; i++)   /* Find the matching remote */
	{
		if(remote_info[i].conn_id == conn_id)
		{
			return i;
		}
	}
	return 0xFF;
}


/* Timer to get messages about water level and send notifications to the connected remotes */
void notifyTimer( void* arg )
{
	static uint8_t leftLevelPrev = 0xFF;
	static uint8_t rightLevelPrev = 0xFF;

	uint8_t i;

	if(leftLevelPrev != levelGetLeft()) /* Left water level has changed */
	{
		leftLevelPrev = levelGetLeft();

		for(i=0; i < REMOTE_MAX; i++)
		{
			if(remote_info[i].conn_id != 0) /* Is this remote connected */
			{
				/* Check if notifications are enabled for this remote */
				if((remote_info[i].cccdWaterLeft & GATT_CLIENT_CONFIG_NOTIFICATION) == GATT_CLIENT_CONFIG_NOTIFICATION)
				{
					wiced_bt_gatt_send_notification(remote_info[i].conn_id,
							HDLC_CONTROLLER_WATERLEVELLEFTBLE_VALUE,
							sizeof(leftLevelPrev),
							&leftLevelPrev);
				}
			}
		}
	}
	if(rightLevelPrev != levelGetRight())
	{
		rightLevelPrev = levelGetRight();
		for(i=0; i < REMOTE_MAX; i++)
		{
			if(remote_info[i].conn_id != 0) /* Is this remote connected */
			{
				/* Check if notifications are enabled for this remote */
				if((remote_info[i].cccdWaterRight & GATT_CLIENT_CONFIG_NOTIFICATION) == GATT_CLIENT_CONFIG_NOTIFICATION)
				{
					wiced_bt_gatt_send_notification(remote_info[i].conn_id,
							HDLC_CONTROLLER_WATERLEVELRIGHTBLE_VALUE,
							sizeof(rightLevelPrev),
							&rightLevelPrev);
				}
			}
		}
	}
}


/* This function handles the scan results */
static void game_scan_result_cback( wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data )
{
	wiced_result_t         status;
	wiced_bool_t           ret_status;
	uint8_t                length;
	uint8_t *              p_data;

	if ( p_scan_result )
	{
		uint8_t manuf_data[] = {0x31, 0x01, 'R', 'e', 'm', 'o', 't', 'e'};
		p_data = wiced_bt_ble_check_advertising_data( p_adv_data, BTM_BLE_ADVERT_TYPE_MANUFACTURER, &length );

		/* Exit if this isn't the device we are looking for */
		if ( ( p_data == NULL ) || ( length != sizeof(manuf_data) ) || ( memcmp( p_data, manuf_data, sizeof(manuf_data) ) != 0 ) )
		{
			// Not a matching device
			return;
		}
#if 0
		WPRINT_APP_INFO((" Found Device: %02X:%02X:%02X:%02X:%02X:%02X \n",
				p_scan_result->remote_bd_addr[0], p_scan_result->remote_bd_addr[1], p_scan_result->remote_bd_addr[2],
				p_scan_result->remote_bd_addr[3], p_scan_result->remote_bd_addr[4], p_scan_result->remote_bd_addr[5] ));
#endif
		/* Stop the scan if we will have max number of remotes connected after this one connects or if scan is disabled */
		/* GJL: add check for enableBleScanning */
		if((remote_cnt >= REMOTE_MAX-1) || (enableBleScanning == WICED_FALSE ))
		{
			if( wiced_bt_ble_get_current_scan_state() != BTM_BLE_SCAN_TYPE_NONE )
			{
				status = wiced_bt_ble_scan( BTM_BLE_SCAN_TYPE_NONE, WICED_FALSE, game_scan_result_cback );
				WPRINT_APP_INFO(( "scan off status %d\n", status ));
			}
		}
		/* Initiate the connection */
		ret_status = wiced_bt_gatt_le_connect( p_scan_result->remote_bd_addr, p_scan_result->ble_addr_type, BLE_CONN_MODE_HIGH_DUTY, TRUE );
		WPRINT_APP_INFO(( "wiced_bt_gatt_le_connect status %d\n", ret_status ));
	}
}


wiced_bt_gatt_status_t game_gatt_callback( wiced_bt_gatt_evt_t event, wiced_bt_gatt_event_data_t *p_data)
{
	wiced_bt_gatt_attribute_request_t *p_attr_req = NULL;
	wiced_bt_gatt_connection_status_t *p_conn_status = NULL;
	uint8_t remote_id;

	switch( event )
	{
	case GATT_CONNECTION_STATUS_EVT:
		p_conn_status = &p_data->connection_status;
		if ( p_conn_status->connected )
		{
			game_add_remote_info( p_conn_status->conn_id, p_conn_status->bd_addr );

			WPRINT_APP_INFO(( "Connected to a new Remote: ID: %d, Addr:<%02X:%02X:%02X:%02X:%02X:%02X>\n ", p_conn_status->conn_id,
					p_conn_status->bd_addr[0], p_conn_status->bd_addr[1], p_conn_status->bd_addr[2],
					p_conn_status->bd_addr[3], p_conn_status->bd_addr[4], p_conn_status->bd_addr[5]));
			WPRINT_APP_INFO(( "Number of connected Remotes: %d\n", remote_cnt ));
		}
		else
		{
			game_remove_remote_info( p_conn_status->conn_id ); /* Remove the remote info */

			WPRINT_APP_INFO(( "Disconnecting remote: ID: %d, Addr: <%02X:%02X:%02X:%02X:%02X:%02X>\n", p_conn_status->conn_id,
					p_conn_status->bd_addr[0], p_conn_status->bd_addr[1], p_conn_status->bd_addr[2],
					p_conn_status->bd_addr[3], p_conn_status->bd_addr[4], p_conn_status->bd_addr[5]));
			WPRINT_APP_INFO(( "Number of connected Remotes: %d\n", remote_cnt ));

			/* If we have less than the max number of remotes, start scanning */
			/* GJL: Add check for enableBleScanning variable */
			if((remote_cnt < REMOTE_MAX) && (enableBleScanning == WICED_TRUE))
			{
				if( wiced_bt_ble_get_current_scan_state() == BTM_BLE_SCAN_TYPE_NONE )
				{
					wiced_bt_ble_scan( BTM_BLE_SCAN_TYPE_HIGH_DUTY, WICED_FALSE, game_scan_result_cback );
				}
			}
		}
		break;

	case GATT_ATTRIBUTE_REQUEST_EVT:
		p_attr_req = &p_data->attribute_request;
		if( p_attr_req->request_type == GATTS_REQ_TYPE_WRITE)
		{
			switch(p_attr_req->data.write_req.handle)
			{
			case HDLC_CONTROLLER_PUMPLEFTBLE_VALUE:
				pumpsSendValues(p_attr_req->data.write_req.p_val[0],0);
				break;
			case HDLC_CONTROLLER_PUMPRIGHTBLE_VALUE:
				pumpsSendValues(0,p_attr_req->data.write_req.p_val[0]);

				break;
			case HDLD_CONTROLLER_WATERLEVELLEFTBLE_CLIENT_CONFIGURATION:
				remote_id = game_get_remote_info(p_attr_req->conn_id);
				if(remote_id < REMOTE_MAX)
				{
					/* Values are sent little endian, so need to swap here */
					remote_info[remote_id].cccdWaterLeft = ((p_attr_req->data.write_req.p_val[1] << 8) | (p_attr_req->data.write_req.p_val[0]));
				}
				break;
			case HDLD_CONTROLLER_WATERLEVELRIGHTBLE_CLIENT_CONFIGURATION:
				remote_id = game_get_remote_info(p_attr_req->conn_id);
				if(remote_id < REMOTE_MAX)
				{
					/* Values are sent little endian, so need to swap here */
					remote_info[remote_id].cccdWaterRight = ((p_attr_req->data.write_req.p_val[1] << 8) | (p_attr_req->data.write_req.p_val[0]));
				}
				break;
			}
		}
		break;

	default:
		break;
	}

	return WICED_BT_GATT_SUCCESS;
}


wiced_result_t game_management_cback( wiced_bt_management_evt_t event,  wiced_bt_management_evt_data_t *p_event_data)
{
	wiced_result_t              result = WICED_BT_SUCCESS;
	wiced_bt_gatt_status_t      gatt_status;

	switch( event )
	{
	/* Bluetooth  stack enabled */
	case BTM_ENABLED_EVT:

		WPRINT_APP_INFO(("Bluetooth Enabled (%s)\n",
				((WICED_BT_SUCCESS == p_event_data->enabled.status) ? "success" : "failure")));

		wiced_rtos_set_event_flags(	&startFlags,	TASK_FLAG_BLE);

		/* Register with stack to receive GATT callback */
		gatt_status = wiced_bt_gatt_register( game_gatt_callback );

		WPRINT_APP_INFO(( "\n wiced_bt_gatt_register: %d\n", gatt_status ));

		/*  Tell stack to use GATT database */
		gatt_status =  wiced_bt_gatt_db_init( gatt_database, gatt_database_len );

		WPRINT_APP_INFO( ( "wiced_bt_gatt_db_init %d\n", gatt_status ) );

		/* Clear out structure that holds info for up to 2 remotes */
		memset( &remote_info, 0, sizeof( remote_info ) );

		/* Start looking for remotes */
		/* GJL: add check for enableBleScanning */
		if((wiced_bt_ble_get_current_scan_state() == BTM_BLE_SCAN_TYPE_NONE) && (enableBleScanning == WICED_TRUE))
		{
			result = wiced_bt_ble_scan( BTM_BLE_SCAN_TYPE_HIGH_DUTY, WICED_FALSE, game_scan_result_cback );
			WPRINT_APP_INFO(( "Start Scanning: %d\n", result ));
		}

		/* Start timer to get water level changes and send notifications if they are enabled */
		wiced_rtos_init_timer(&notify_timer_handle, TIMEOUT_IN_MS, notifyTimer, NULL);
		wiced_rtos_start_timer(&notify_timer_handle);
		break;

	case BTM_PAIRED_DEVICE_LINK_KEYS_REQUEST_EVT:
		//WPRINT_APP_INFO(("Paired Keys Request\r\n"));
		result = WICED_BT_ERROR; /* No keys stored in NVRAM so indicate that there are no keys */
		break;

	case BTM_LOCAL_IDENTITY_KEYS_UPDATE_EVT:
		//WPRINT_APP_INFO(("Local Keys Update\r\n"));
		/* No keys stored in NVRAM so no need to do anything here */
		break;

	case BTM_LOCAL_IDENTITY_KEYS_REQUEST_EVT:
		//WPRINT_APP_INFO(("Local Keys Request\r\n"));
		result = WICED_BT_ERROR; /* No keys stored in NVRAM so indicate that there are no keys */
		break;

	case BTM_BLE_SCAN_STATE_CHANGED_EVT:
		WPRINT_APP_INFO(( "Scan State Change: %d\n", p_event_data->ble_scan_state_changed ));
		break;

	case BTM_LPM_STATE_LOW_POWER:
		/* No low power implementation */
		break;

	default:
		WPRINT_APP_INFO(("Unhandled Bluetooth Management Event: 0x%x (%d)\n", event, event));
		break;
	}
	return result;
}


void startBle( void )
{
	wiced_bt_stack_init( game_management_cback,
			&wiced_bt_cfg_settings, wiced_bt_cfg_buf_pools );
}


/* GJL: add this function to turn BLE scanning on/off */
/* Scanning is turned off when a game starts and is turned on when the game ends */
/* The command console can also be used to turn scanning on/off */
void bleScanMode(wiced_bool_t mode)
{
	wiced_result_t result;

	if(mode == WICED_TRUE)
	{
		enableBleScanning = WICED_TRUE;
		if( wiced_bt_ble_get_current_scan_state() == BTM_BLE_SCAN_TYPE_NONE )
		{
			result = wiced_bt_ble_scan( BTM_BLE_SCAN_TYPE_HIGH_DUTY, WICED_FALSE, game_scan_result_cback );
			WPRINT_APP_INFO(( "Start Scanning: %d\n", result ));
		}
	}
	else
	{
		enableBleScanning = WICED_FALSE;
		if( wiced_bt_ble_get_current_scan_state() != BTM_BLE_SCAN_TYPE_NONE )
		{
			result = wiced_bt_ble_scan( BTM_BLE_SCAN_TYPE_NONE, WICED_FALSE, game_scan_result_cback );
			WPRINT_APP_INFO(( "Stop BLE Scanning: %d\n", result ));
		}
	}
}
