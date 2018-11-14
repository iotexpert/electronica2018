#include "wiced.h"
#include "aws_common.h"
#include "wiced_aws.h"
#include "aws.h"
#include "resources.h"
#include "game.h"
#include "liquidlevel.h"
#include "pumps.h"
#include "globals.h"
#include "resources.h"
#include "cJSON.h"

/******************************************************
 *                      Macros
 ******************************************************/
#define AWS_TIMEOUT 		500
#define AWS_CONNECT_TIMEOUT 10000

#define AWS_PUB_DELAY    					       (5000)
#define PUBLISHER_CERTIFICATES_MAX_SIZE            (0x7fffffff)

#define AWS_IOT_MQTT_BROKER_ADDRESS                	"amk6m51qrxr2u-ats.iot.us-east-1.amazonaws.com"
#define SUBSCRIBE_TOPIC                     		"PumpAWS"
#define SHADOW_PUBLISH_TOPIC						"$aws/things/Electronica2018/shadow/update"

#define APP_PUBLISH_RETRY_COUNT                    (5)

/******************************************************
 *               Variable Definitions
 ******************************************************/
static wiced_bool_t       is_connected = WICED_FALSE;
wiced_mac_t mac; 	/* Device MAC address */


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

/* Array to send messages to the display thread */

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
    result = resource_get_readonly_buffer( &resources_aws_client_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) &security->certificate );
    if( result != WICED_SUCCESS )
    {
        goto _fail_client_certificate;
    }
    if(size_out < 64)
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Device Certificate! Replace the dummy certificate with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/publisher/'client.cer']\n\n" ) );
        resource_free_readonly_buffer( &resources_aws_client_cer, (const void *)security->certificate );
        goto _fail_client_certificate;
    }

    security->certificate_length = size_out;

    /* Get Publisher's Private Key filename: 'privkey.cer' located @ resources/apps/aws/iot/publisher folder */
    result = resource_get_readonly_buffer( &resources_aws_privkey_cer, 0, PUBLISHER_CERTIFICATES_MAX_SIZE, &size_out, (const void **) &security->private_key );
    if( result != WICED_SUCCESS )
    {
        goto _fail_private_key;
    }
    if(size_out < 64)
    {
        WPRINT_APP_INFO( ( "\n[Application/AWS] Invalid Device Private-Key! Replace the dummy Private-key with AWS one[<YOUR_WICED_SDK>/resources/app/aws/iot/publisher/'privkey.cer'\n\n" ) );
        resource_free_readonly_buffer( &resources_aws_privkey_cer, (const void *)security->private_key );
        goto _fail_private_key;
    }
    security->key_length = size_out;

    return WICED_SUCCESS;

_fail_private_key:
    resource_free_readonly_buffer( &resources_aws_client_cer, (const void *)security->certificate );
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
    {
        return;
    }

	cJSON *root;
	cJSON *left;
	cJSON *right;

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
        		WPRINT_APP_INFO(("Subscribed\n"));
            break;

        case WICED_AWS_EVENT_PAYLOAD_RECEIVED:
    		root = cJSON_Parse((char*) data->message.data);
    		left = cJSON_GetObjectItem(root,"left");
    		right = cJSON_GetObjectItem(root,"right");
    		uint8_t leftValue=0;
    		uint8_t rightValue= 0;

    		if(left && cJSON_IsNumber(left))
    		{
    			leftValue = left->valueint;
    		}

    		if(right && cJSON_IsNumber(right))
    		{
    			rightValue = right->valueint;
    		}
    		cJSON_Delete(root);

    		pumpsSendValues(leftValue,rightValue);

    		break;
            break;

        case WICED_AWS_EVENT_PUBLISHED:
        case WICED_AWS_EVENT_UNSUBSCRIBED:
        default:
            break;
    }
}

/* Thread that publishes a value on a regular interval */
void awsThread(wiced_thread_arg_t arg)
{
    wiced_aws_handle_t aws_connection = 0;
    wiced_result_t ret = WICED_SUCCESS;
    int pub_retries;
    char msg[100]; /* This will hold the JSON message to be published */
    char thingName[] = "remote001122334455"; /* This gets replaced with the MAC address */

    uint32_t waterLevelLeft  = 0;
    uint32_t waterLevelRight = 0;

    wiced_wifi_get_mac_address(&mac);

    wiced_rtos_init_semaphore(&aws_semaphore_handle);

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

    wiced_aws_thing_info_t my_publisher_aws_config = {
        .name            = thingName,
        .credentials     = &my_publisher_security_creds,
    };

    /* Load certificates and keys from the resources */
    get_aws_credentials_from_resources();

    /* Display message */

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
			WPRINT_APP_INFO(("AWS: connect attempt...\n"));
			wiced_aws_connect(aws_connection);

			/* Wait until connection is done - the semaphore is set in the AWS connect callback */
			ret = wiced_rtos_get_semaphore(&aws_semaphore_handle, AWS_CONNECT_TIMEOUT);
		} while (ret != WICED_SUCCESS); /* We will stay in this loop until the AWS connection has been made */

		/* Subscribe to the shadow update topic (to get water level updates) */
		wiced_aws_subscribe( aws_connection, SUBSCRIBE_TOPIC,   WICED_AWS_QOS_ATMOST_ONCE);


		while ( 1 ) /* Loop to publish water level every 500ms to AWS */
		{
			wiced_rtos_delay_milliseconds(500);

			/* GJL: Add section to publish water levels every 500ms and to attempt reconnect if we are not connected or publish fails */
			/* Get water levels */
			waterLevelLeft  = levelGetLeft();
			waterLevelRight = levelGetRight();

			/* Create JSON message with the water levels */
			snprintf(msg, sizeof(msg), "{\"state\":{\"reported\":{\"WaterLevelLeftAWS\":%.0d,\"WaterLevelRightAWS\":%.0d}}}", (uint8_t) waterLevelLeft, (uint8_t) waterLevelRight);

			/* Publish water levels to AWS */
			pub_retries = 0;
			if ( is_connected != WICED_FALSE )
			{
				do
				{
					ret = wiced_aws_publish( aws_connection, SHADOW_PUBLISH_TOPIC, (uint8_t *)msg, strlen( msg ), WICED_AWS_QOS_ATMOST_ONCE );
					pub_retries++ ;
				} while ( ( ret != WICED_SUCCESS ) && ( pub_retries < APP_PUBLISH_RETRY_COUNT ) );
				if ( ret != WICED_SUCCESS )
				{
					WPRINT_APP_INFO(("Publish of Water Level Failed\r\n"));
					break; /* Break out of loop to try reconnecting */
				}
			}
			else
			{
				break; /* Exit to reconnect */
			}

		} /* End of inner while(1) loop that publishes water level every 500ms */

		WPRINT_APP_INFO(("[Application/AWS] Closing connection...\r\n"));
		wiced_aws_disconnect( aws_connection );

		WPRINT_APP_INFO(("[Application/AWS] Deinitializing AWS library...\r\n"));
		ret = wiced_aws_deinit( );

	} /* End of outer while(1) that will reconnect if the connection is lost */
}


