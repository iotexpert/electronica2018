/*
Thread to handle AWS operations
 */

#include "global.h"
#include "wiced.h"
#include "wiced_aws.h"
#include "aws_common.h"
#include "resources.h"
#include "cJSON.h"
#include "capsense_app.h"
#include "display_app.h"

/******************************************************
 *                      Macros
 ******************************************************/
#define AWS_TIMEOUT 		500
#define AWS_CONNECT_TIMEOUT 10000

#define AWS_PUB_DELAY    					       (5000)
#define PUBLISHER_CERTIFICATES_MAX_SIZE            (0x7fffffff)

#define AWS_IOT_MQTT_BROKER_ADDRESS                	"amk6m51qrxr2u-ats.iot.us-east-1.amazonaws.com"
#define PUMP_PUBLISH_TOPIC                          "PumpAWS"
#define SHADOW_UPDATE_SUBSCRIBE_TOPIC				"$aws/things/Electronica2018/shadow/update/accepted"

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

static wiced_semaphore_t aws_semaphore_handle;

/* Water level % pulled from AWS */
static uint8_t waterLeft  = 0;
static uint8_t waterRight = 0;

/* Array to send messages to the display thread */
static int8_t displayCommand[DISPLAY_MESSAGE_SIZE] = {0};

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

    /* Get AWS Root CA certificate filename: 'rootca.cer' located @ resources folder */
    result = resource_get_readonly_buffer( &resources_rootca_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) root_ca_certificate);
    if( result != WICED_SUCCESS )
    {
        goto _fail_aws_certificate;
    }
    if( size_out < 64 )
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Root CA Certificate! Replace the dummy certificate with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/'rootca.cer']\n\n" ) );
        resource_free_readonly_buffer( &resources_rootca_cer, (const void *)*root_ca_certificate );
        goto _fail_aws_certificate;
    }

    my_publisher_aws_iot_endpoint.root_ca_length = size_out;

    /* Get Publisher's Certificate filename: 'client.cer' located @ resources/apps/aws/iot/pubisher folder */
    result = resource_get_readonly_buffer( &resources_client_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) &security->certificate );
    if( result != WICED_SUCCESS )
    {
        goto _fail_client_certificate;
    }
    if(size_out < 64)
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Device Certificate! Replace the dummy certificate with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/publisher/'client.cer']\n\n" ) );
        resource_free_readonly_buffer( &resources_client_cer, (const void *)security->certificate );
        goto _fail_client_certificate;
    }

    security->certificate_length = size_out;

    /* Get Publisher's Private Key filename: 'privkey.cer' located @ resources/apps/aws/iot/publisher folder */
    result = resource_get_readonly_buffer( &resources_privkey_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) &security->private_key );
    if( result != WICED_SUCCESS )
    {
        goto _fail_private_key;
    }
    if(size_out < 64)
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Device Private-Key! Replace the dummy Private-key with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/publisher/'privkey.cer'\n\n" ) );
        resource_free_readonly_buffer( &resources_privkey_cer, (const void *)security->private_key );
        goto _fail_private_key;
    }
    security->key_length = size_out;

    return WICED_SUCCESS;

_fail_private_key:
    resource_free_readonly_buffer( &resources_client_cer, (const void *)security->certificate );
_fail_client_certificate:
    resource_free_readonly_buffer( &resources_rootca_cer, (const void *)*root_ca_certificate );
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
            /* Print Water Levels */
            displayCommand[DISPLAY_CMD] =  GAME_SCREEN;
            displayCommand[DISPLAY_TYPE] = WATER_VALUE;
            displayCommand[DISPLAY_VAL1] = waterLeft;
            displayCommand[DISPLAY_VAL2] = waterRight;
        	wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, AWS_TIMEOUT);
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
    uint8_t queueMessage[SWIPE_MESSAGE_SIZE] = {0}; /* This is the message sent from the CapSense queue */
    char thingName[] = "remote001122334455"; /* This gets replaced with the MAC address */

    wiced_rtos_init_semaphore(&aws_semaphore_handle);

    /* Set up WiFi Screen */
    displayCommand[DISPLAY_CMD] =  WIFI_SCREEN;
    displayCommand[DISPLAY_TYPE] = WIFI_CONNECT;
	wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, AWS_TIMEOUT);

    /* Bring up the network interface */
    do
    {
    	ret = wiced_network_up( WICED_AWS_DEFAULT_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
    	wiced_rtos_delay_milliseconds(100); /* Wait if connection didn't happen before trying again */
    } while (ret != WICED_SUCCESS);

    /* Set Thing name to device MAC address */
    snprintf(thingName, sizeof(thingName),
    		"remote%02X%02X%02X%02X%02X%02X",
			mac.octet[0], mac.octet[1], mac.octet[2],
			mac.octet[3], mac.octet[4], mac.octet[5]);

    /* Display message */
    displayCommand[DISPLAY_CMD] =  WIFI_SCREEN;
    displayCommand[DISPLAY_TYPE] = AWS_RESOURCES;
	wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, AWS_TIMEOUT);

    wiced_aws_thing_info_t my_publisher_aws_config = {
        .name            = thingName,
        .credentials     = &my_publisher_security_creds,
    };

    /* Load certificates and keys from the resources */
    get_aws_credentials_from_resources();

    /* Display message */
    displayCommand[DISPLAY_CMD] =  WIFI_SCREEN;
    displayCommand[DISPLAY_TYPE] = AWS_CONNECT;
	wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, AWS_TIMEOUT);

	/* This outer loop is used to attempt to reconnect if the connection is lost */
	while(1)
	{

		/* Initialize AWS and set up connection handle */
		wiced_aws_init( &my_publisher_aws_config , my_publisher_aws_callback );
		aws_connection = (wiced_aws_handle_t)wiced_aws_create_endpoint(&my_publisher_aws_iot_endpoint);
		my_app_aws_handle = aws_connection;

		/* Connect to the server. If the connection doesn't happen before AWS_CONNECT_TIMEOUT, disconnect and attempt to connect again */
		WPRINT_APP_INFO(("[Application/AWS] Opening connection...\n"));
		do
		{
			WPRINT_APP_INFO(("GJL: connect attempt...\n"));
			wiced_aws_connect(aws_connection);

			/* Wait until connection is done - the semaphore is set in the AWS connect callback */
			ret = wiced_rtos_get_semaphore(&aws_semaphore_handle, AWS_CONNECT_TIMEOUT);
		} while (ret != WICED_SUCCESS); /* We will stay in this loop until the AWS connection has been made */

		/* Display message */
		displayCommand[DISPLAY_CMD] =  WIFI_SCREEN;
		displayCommand[DISPLAY_TYPE] = SUBSCRIBE_SHADOW;
		wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, AWS_TIMEOUT);

		/* Subscribe to the shadow update topic (to get water level updates) */
		wiced_aws_subscribe( aws_connection, SHADOW_UPDATE_SUBSCRIBE_TOPIC,   WICED_AWS_QOS_ATLEAST_ONCE);

		/* Display message */
		wiced_rtos_delay_milliseconds(250); /* Wait before switching screens */
		displayCommand[DISPLAY_CMD] =  GAME_SCREEN;
		displayCommand[DISPLAY_TYPE] = INIT_WIFI;
		wiced_rtos_push_to_queue(&display_queue_handle, &displayCommand, AWS_TIMEOUT);

		while ( 1 ) /* Loop to wait for swipe messages and publish to AWS */
		{
			/* Wait for a new message in the queue */
			wiced_rtos_pop_from_queue(&swipe_queue_handle, &queueMessage, WICED_WAIT_FOREVER);
			if(queueMessage[0] == SWIPE_RIGHT)
			{
				snprintf(msg, sizeof(msg), "{\"Right\" : %.0d}", queueMessage[1]);
			}
			else /* SWIPE_LEFT */
			{
				snprintf(msg, sizeof(msg), "{\"Left\" : %.0d}",  queueMessage[1]);
			}

			pub_retries = 0;
			if ( is_connected != WICED_FALSE )
			{
				WPRINT_APP_INFO(("[Application/AWS] Publishing..."));
				do
				{
					ret = wiced_aws_publish( aws_connection, PUMP_PUBLISH_TOPIC, (uint8_t *)msg, strlen( msg ), WICED_AWS_QOS_ATMOST_ONCE );
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
			else
			{
				break; /* Exit to reconnect */
			}
		} /* End of inner while(1) loop that waits for swipe values and publishes them */

		WPRINT_APP_INFO(("[Application/AWS] Closing connection...\r\n"));
		wiced_aws_disconnect( aws_connection );

		WPRINT_APP_INFO(("[Application/AWS] Deinitializing AWS library...\r\n"));
		ret = wiced_aws_deinit( );

	} /* End of outer while(1) that will reconnect if the connection is lost */
}
