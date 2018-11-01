/*
Thread to handle AWS operations
 */

#include "wiced.h"
#include "wiced_aws.h"
#include "aws_common.h"
#include "resources.h"
#include "cJSON.h"
#include "global.h"

/******************************************************
 *                      Macros
 ******************************************************/
#define AWS_PUB_DELAY    					       (5000)
#define PUBLISHER_CERTIFICATES_MAX_SIZE            (0x7fffffff)

#define AWS_IOT_MQTT_BROKER_ADDRESS                	"amk6m51qrxr2u-ats.iot.us-east-1.amazonaws.com"
#define PUMP_PUBLISH_TOPIC                          "PumpAWS"
#define SHADOW_UPDATE_SUBSCRIBE_TOPIC				"$aws/things/Electronica2018/shadow/update/accepted"
#define SHADOW_GET_PUBLISH_TOPIC					"$aws/things/Electronica2018/shadow/get"
#define SHADOW_GET_SUBSCRIBE_TOPIC					"$aws/things/Electronica2018/shadow/get/accepted"

#define APP_PUBLISH_RETRY_COUNT                    (5)

/******************************************************
 *               Variable Definitions
 ******************************************************/
static wiced_bool_t       is_connected = WICED_FALSE;

static wiced_aws_thing_security_info_t my_publisher_security_creds =
{
    .private_key         = NULL,
    .key_length          = 0,
    .certificate         = NULL,
    .certificate_length  = 0,
};

static wiced_aws_endpoint_info_t my_publisher_aws_iot_endpoint = {
    .transport           = WICED_AWS_TRANSPORT_MQTT_NATIVE,
    .uri                 = AWS_IOT_MQTT_BROKER_ADDRESS,
    .peer_common_name    = NULL,
    .ip_addr             = {0},
    .port                = WICED_AWS_IOT_DEFAULT_MQTT_PORT,
    .root_ca_certificate = NULL,
    .root_ca_length      = 0,
};

static wiced_aws_handle_t my_app_aws_handle;

wiced_semaphore_t aws_semaphore_handle;

/* Water level % pulled from AWS */
uint8_t waterLeft  = 0;
uint8_t waterRight = 0;

/******************************************************
 *                Function Definitions
 ******************************************************/
static wiced_result_t get_aws_credentials_from_resources( void )
{
    uint32_t size_out = 0;
    wiced_result_t result = WICED_ERROR;

    wiced_aws_thing_security_info_t* security = &my_publisher_security_creds;
    uint8_t** root_ca_certificate = &my_publisher_aws_iot_endpoint.root_ca_certificate;

    if( security->certificate && security->private_key && (*root_ca_certificate) )
    {
        WPRINT_APP_INFO(("\n[Application/AWS] Security Credentials already set(not NULL). Abort Reading from Resources...\n"));
        return WICED_SUCCESS;
    }

    /* Get AWS Root CA certificate filename: 'rootca.cer' located @ resources/apps/aws/iot folder */
    result = resource_get_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_rootca_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) root_ca_certificate);
    if( result != WICED_SUCCESS )
    {
        goto _fail_aws_certificate;
    }
    if( size_out < 64 )
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Root CA Certificate! Replace the dummy certificate with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/'rootca.cer']\n\n" ) );
        resource_free_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_rootca_cer, (const void *)*root_ca_certificate );
        goto _fail_aws_certificate;
    }

    my_publisher_aws_iot_endpoint.root_ca_length = size_out;

    /* Get Publisher's Certificate filename: 'client.cer' located @ resources/apps/aws/iot/pubisher folder */
    result = resource_get_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_publisher_DIR_client_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) &security->certificate );
    if( result != WICED_SUCCESS )
    {
        goto _fail_client_certificate;
    }
    if(size_out < 64)
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Device Certificate! Replace the dummy certificate with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/publisher/'client.cer']\n\n" ) );
        resource_free_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_publisher_DIR_client_cer, (const void *)security->certificate );
        goto _fail_client_certificate;
    }

    security->certificate_length = size_out;

    /* Get Publisher's Private Key filename: 'privkey.cer' located @ resources/apps/aws/iot/publisher folder */
    result = resource_get_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_publisher_DIR_privkey_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) &security->private_key );
    if( result != WICED_SUCCESS )
    {
        goto _fail_private_key;
    }
    if(size_out < 64)
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Device Private-Key! Replace the dummy Private-key with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/publisher/'privkey.cer'\n\n" ) );
        resource_free_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_publisher_DIR_privkey_cer, (const void *)security->private_key );
        goto _fail_private_key;
    }
    security->key_length = size_out;

    return WICED_SUCCESS;

_fail_private_key:
    resource_free_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_publisher_DIR_client_cer, (const void *)security->certificate );
_fail_client_certificate:
    resource_free_readonly_buffer( &resources_apps_DIR_aws_DIR_iot_DIR_rootca_cer, (const void *)*root_ca_certificate );
_fail_aws_certificate:
    return WICED_ERROR;
}

/*
 * Call back function to handle AWS events.
 */
static void my_publisher_aws_callback( wiced_aws_handle_t aws, wiced_aws_event_type_t event, wiced_aws_callback_data_t* data )
{
    if( !aws || !data || (aws != my_app_aws_handle) )
        return;

    cJSON *root;
    cJSON *state;
	cJSON *reported;

    switch ( event )
    {
        case WICED_AWS_EVENT_CONNECTED:
        	if( data->connection.status == WICED_SUCCESS )
            {
                is_connected = WICED_TRUE;
            }
            wiced_rtos_set_semaphore(&aws_semaphore_handle);
            break;

        case WICED_AWS_EVENT_DISCONNECTED:
        	if( data->disconnection.status == WICED_SUCCESS )
            {
                is_connected = WICED_FALSE;
            }
            break;

        case WICED_AWS_EVENT_SUBSCRIBED:
            WPRINT_APP_INFO( ( "GJL SUBSCRIPTION EVENT\n") ); // GJL - never get this callback ????
            break;

        case WICED_AWS_EVENT_PAYLOAD_RECEIVED:
            /* Parse JSON message for the water level data */
        	root = cJSON_Parse((char*) data->message.data);
        	state = cJSON_GetObjectItem(root,"state");
        	reported = cJSON_GetObjectItem(state,"reported");
            waterLeft = (uint8_t) cJSON_GetObjectItem(reported,"WaterLevelLeftAWS")->valuedouble;
            waterRight = (uint8_t) cJSON_GetObjectItem(reported,"WaterLevelRightAWS")->valuedouble;
        	cJSON_Delete(root); /* Free up memory */
            WPRINT_APP_INFO( ( "Water Left: %d\t Water Right: %d\n", waterLeft, waterRight) );
            break;

        case WICED_AWS_EVENT_PUBLISHED:
        case WICED_AWS_EVENT_UNSUBSCRIBED:
        default:
            break;
    }
}

/* Thread that publishes a value on a regular interval */
void awsThread( void )
{
    wiced_aws_handle_t aws_connection = 0;
    wiced_result_t ret = WICED_SUCCESS;
    int pub_retries;
    char msg[18]; /* This will hold the JSON message to be published */
    uint16_t queueMessage[2]; /* This is the message send from the slider via the RTOS queue */
    char thingName[] = "remote001122334455"; /* This gets replaced with the MAC address */

    wiced_rtos_init_semaphore(&aws_semaphore_handle);

    /* Bring up the network interface */
    ret = wiced_network_up( WICED_AWS_DEFAULT_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
    if ( ret != WICED_SUCCESS )
    {
        WPRINT_APP_INFO( ( "[Application/AWS] Not able to join the requested AP\n\n" ) );
        return;
    }


    /* Set Thing name to device MAC address */
    snprintf(thingName, sizeof(thingName),
    		"remote%02X%02X%02X%02X%02X%02X",
			mac.octet[0], mac.octet[1], mac.octet[2],
			mac.octet[3], mac.octet[4], mac.octet[5]);

    wiced_aws_thing_info_t my_publisher_aws_config = {
        .name            = thingName,
        .credentials     = &my_publisher_security_creds,
    };

    ret = get_aws_credentials_from_resources();
    if( ret != WICED_SUCCESS )
    {
        WPRINT_APP_INFO( ("[Application/AWS] Error fetching credentials from resources\n" ) );
        return;
    }

    ret = wiced_aws_init( &my_publisher_aws_config , my_publisher_aws_callback );
    if( ret != WICED_SUCCESS )
    {
        WPRINT_APP_INFO( ( "[Application/AWS] Failed to Initialize AWS library\n\n" ) );
        return;
    }

    aws_connection = (wiced_aws_handle_t)wiced_aws_create_endpoint(&my_publisher_aws_iot_endpoint);
    if( !aws_connection )
    {
        WPRINT_APP_INFO( ( "[Application/AWS] Failed to create AWS connection handle\n\n" ) );
        return;
    }

    my_app_aws_handle = aws_connection;

    WPRINT_APP_INFO(("[Application/AWS] Opening connection...\n"));
    ret = wiced_aws_connect(aws_connection);
    if ( ret != WICED_SUCCESS )
    {
        WPRINT_APP_INFO(("[Application/AWS] Connect Failed\r\n"));
        return;
    }

    /* Wait until connection is done */
    wiced_rtos_get_semaphore(&aws_semaphore_handle, WICED_WAIT_FOREVER); //GJL might want a timeout here

    /* Subscribe to the shadow update topic (to get water level updates) and shadow/get/accepted to get initial water levels */
    ret = wiced_aws_subscribe( aws_connection, SHADOW_UPDATE_SUBSCRIBE_TOPIC,   WICED_AWS_QOS_ATLEAST_ONCE);
    ret = wiced_aws_subscribe( aws_connection, SHADOW_GET_SUBSCRIBE_TOPIC, 		WICED_AWS_QOS_ATLEAST_ONCE);

    wiced_rtos_delay_milliseconds(1000); // GJL TEMP - need to wait for subscription to finish - never get a callback for the subscribes

    /* Get starting water levels by publishing to shadow/get - this causes a message to be published to shadow/get/accepted with the shadow state */
	wiced_aws_publish( aws_connection, SHADOW_GET_PUBLISH_TOPIC, (uint8_t*)"{}", strlen(msg),  WICED_AWS_QOS_ATLEAST_ONCE );

    nextState = CONNECTED; // Indicate to main that the connection is now active

    while ( 1 )
    {
    	/* Wait for a new message in the queue */
		wiced_rtos_pop_from_queue(&swipe_queue_handle, &queueMessage, WICED_WAIT_FOREVER);
		if(queueMessage[0] == RIGHT)
		{
			snprintf(msg, sizeof(msg), "{\"Right\" : %.0d}", queueMessage[1]);
		}
		else
		{
			snprintf(msg, sizeof(msg), "{\"Left\" : %.0d}",  queueMessage[1]);
		}

        pub_retries = 0;
        if ( is_connected != WICED_FALSE )
        {
			WPRINT_APP_INFO(("[Application/AWS] Publishing..."));
			do
			{
				ret = wiced_aws_publish( aws_connection, PUMP_PUBLISH_TOPIC, (uint8_t *)msg, strlen( msg ), WICED_AWS_QOS_ATLEAST_ONCE );
				pub_retries++ ;
			} while ( ( ret != WICED_SUCCESS ) && ( pub_retries < APP_PUBLISH_RETRY_COUNT ) );
			if ( ret != WICED_SUCCESS )
			{
				WPRINT_APP_INFO((" Failed\r\n"));
				break;
			}
			else
			{
				WPRINT_APP_INFO((" Success\r\n"));
			}
        }
    }

    WPRINT_APP_INFO(("[Application/AWS] Closing connection...\r\n"));
    wiced_aws_disconnect( aws_connection );

    WPRINT_APP_INFO(("[Application/AWS] Deinitializing AWS library...\r\n"));
    ret = wiced_aws_deinit( );

    return;
}
