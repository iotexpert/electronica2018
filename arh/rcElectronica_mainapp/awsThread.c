

#include "wiced.h"
#include "wiced_aws.h"
#include "aws_common.h"

#include "resources.h"

/******************************************************
 *                      Macros
 ******************************************************/

#define APPLICATION_DELAY_IN_MILLISECONDS          (1000)

#define PUBLISHER_CERTIFICATES_MAX_SIZE            (0x7fffffff)


#define WICED_TOPIC                                "WICED_BULB"
#define MSG_ON                                     "LIGHT ON"
#define MSG_OFF                                    "LIGHT OFF"
#define APP_PUBLISH_RETRY_COUNT                    (5)

/******************************************************
 *               Variable Definitions
 ******************************************************/

static wiced_semaphore_t  wake_semaphore;
static uint8_t            do_publish = 0;
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
    .uri                 = "a38td4ke8seeky-ats.iot.us-east-1.amazonaws.com",
    .peer_common_name    = NULL,
    .ip_addr             = {0},
    .port                = WICED_AWS_IOT_DEFAULT_MQTT_PORT,
    .root_ca_certificate = NULL,
    .root_ca_length      = 0,
};

static wiced_aws_thing_info_t my_publisher_aws_config = {
    .name            = "wiced_ggd_1",
    .credentials     = &my_publisher_security_creds,
};

static wiced_aws_handle_t my_app_aws_handle;


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

	switch ( event )
	{
	case WICED_AWS_EVENT_CONNECTED:
	{
		if( data->connection.status == WICED_SUCCESS )
		{
			is_connected = WICED_TRUE;
		}
	}
	break;

	case WICED_AWS_EVENT_DISCONNECTED:
	{
		if( data->disconnection.status == WICED_SUCCESS )
		{
			is_connected = WICED_FALSE;

		}
	}
	break;

	case WICED_AWS_EVENT_PUBLISHED:
	case WICED_AWS_EVENT_SUBSCRIBED:
	case WICED_AWS_EVENT_UNSUBSCRIBED:
	case WICED_AWS_EVENT_PAYLOAD_RECEIVED:
	default:
		break;
	}
}

/******************************************************
 *               Function Definitions
 ******************************************************/

void awsThread( void )
{
    wiced_aws_handle_t aws_connection = 0;
    wiced_result_t ret = WICED_SUCCESS;
    uint32_t count = 0;
    int pub_retries = 0;
    char*                 msg = MSG_OFF;


    /* Bring up the network interface */
    ret = wiced_network_up( WICED_AWS_DEFAULT_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
    if ( ret != WICED_SUCCESS )
    {
        WPRINT_APP_INFO( ( "[Application/AWS] Not able to join the requested AP\n\n" ) );
        return;
    }

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

    wiced_rtos_init_semaphore( &wake_semaphore );

    WPRINT_APP_INFO(("[Application/AWS] Opening connection...\n"));
    ret = wiced_aws_connect(aws_connection);
    if ( ret != WICED_SUCCESS )
    {
        WPRINT_APP_INFO(("[Application/AWS] Connect Failed\r\n"));
        return;
    }

    wiced_rtos_delay_milliseconds(1500);

    while ( 1 )
    {

    	pub_retries = 0;

    	if ( is_connected == WICED_FALSE )
    	{
    		continue;
    	}

    	WPRINT_APP_INFO(("[Application/AWS] Publishing..."));
    	if ( count % 2 )
    	{
    		msg = MSG_ON;
    	}
    	else
    	{
    		msg = MSG_OFF;
    	}
    	do
    	{
    		ret = wiced_aws_publish( aws_connection, WICED_TOPIC, (uint8_t *)msg, strlen( msg ), WICED_AWS_QOS_ATLEAST_ONCE );
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

    	count++ ;

    	wiced_rtos_delay_milliseconds( 100 );
    }

    WPRINT_APP_INFO(("[Application/AWS] Closing connection...\r\n"));
    wiced_aws_disconnect( aws_connection );

    wiced_rtos_deinit_semaphore( &wake_semaphore );

    WPRINT_APP_INFO(("[Application/AWS] Deinitializing AWS library...\r\n"));
    ret = wiced_aws_deinit( );

    return;
}
