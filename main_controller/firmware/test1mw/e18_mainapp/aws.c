
#include "wiced.h"
#include "aws_common.h"
#include "wiced_aws.h"
#include "aws.h"
#include "resources.h"
#include "cJSON.h"
#include "game.h"

/******************************************************
 *               Variable Definitions
 ******************************************************/

static wiced_bool_t       is_connected = WICED_FALSE;
static wiced_aws_handle_t my_app_aws_handle;
static wiced_bool_t is_subscribed = WICED_FALSE;
static wiced_aws_handle_t aws_connection = 0;
static AWS_STATE_T awsState = AWS_UNINITIALIZED;

AWS_PUBREQ_T levelPublishRequest = NO_PENDING_AWS_PUBREQ;
AWS_INIT_STATE_T awsInitState = AWS_INIT_BASE;

static wiced_aws_thing_security_info_t my_publisher_security_creds =
{
    .private_key         = NULL,        //uint8_t*, pointer to key
    .key_length          = 0,           //uint16_t 
    .certificate         = NULL,        //uint8_t*, pointer to cert
    .certificate_length  = 0,           //uint16_t
};

static wiced_aws_endpoint_info_t my_publisher_aws_iot_endpoint = {
    .transport           = WICED_AWS_TRANSPORT_MQTT_NATIVE,
    .uri                 = "amk6m51qrxr2u-ats.iot.us-east-1.amazonaws.com",
    .peer_common_name    = NULL,
    .ip_addr             = {0},
    .port                = WICED_AWS_IOT_DEFAULT_MQTT_PORT,
    .root_ca_certificate = NULL,
    .root_ca_length      = 0,
};

static wiced_aws_thing_info_t aws_config = {
    .name            = "Electronica2018",
    .credentials     = &my_publisher_security_creds,
};


////static IP for testing in ORDC:
//static const wiced_ip_setting_t device_static_ip_settings =
//{
//    INITIALISER_IPV4_ADDRESS( .ip_address,   MAKE_IPV4_ADDRESS(192, 168,   100,  7) ),
//    INITIALISER_IPV4_ADDRESS( .gateway,      MAKE_IPV4_ADDRESS(192, 168,   100,  1) ),
//    INITIALISER_IPV4_ADDRESS( .netmask,      MAKE_IPV4_ADDRESS(255, 255, 255,  0) ),
//};

#define PUBLISHER_CERTIFICATES_MAX_SIZE            (0x7fffffff)	//wtfffffff


//function prototypes

static void aws_callback(wiced_aws_handle_t aws, wiced_aws_event_type_t event, wiced_aws_callback_data_t* data);
static wiced_result_t get_aws_credentials_from_resources(void);
static AWS_INIT_RESULT_T awsInitMachine(void);
//static wiced_result_t aws_start(void);
//static void awsInit(uint8_t initType);


//code
// void awsInit(uint8_t initType)
// {
// 	//do AWS init stuff
// 	awsState = AWS_INITIALIZED;
// }


// wiced_result_t aws_start( void )
// {
// #define APPLICATION_DELAY_IN_MILLISECONDS          (1000)
// #define APPLICATION_SUBSCRIBE_RETRY_COUNT 3

// 	wiced_result_t ret = WICED_SUCCESS;
//     uint8_t index;
//     int retries = 0;

// 	WPRINT_APP_INFO(("Starting AWS - \n"));

// 	/* Disable roaming to other access points */
// 	wiced_wifi_set_roam_trigger( -99 ); /* -99dBm ie. extremely low signal level */

// 	/* Bring up the network interface */
// 	do {
// 		ret = wiced_network_up( WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
// 		//ret = wiced_network_up(WICED_STA_INTERFACE, WICED_USE_STATIC_IP, &device_static_ip_settings);
// 		if(ret != WICED_SUCCESS)
// 			WPRINT_APP_INFO(("Failed to network up\n"));
// 	} while(ret != WICED_SUCCESS);

//     ret = get_aws_credentials_from_resources();
//     if( ret != WICED_SUCCESS )
//     {
//         WPRINT_APP_INFO( ("[Application/AWS] Error fetching credentials from resources\n" ) );
//         return WICED_ERROR;
//     }

//     ret = wiced_aws_init( &aws_config , aws_callback );
//     if( ret != WICED_SUCCESS )
//     {
//         WPRINT_APP_INFO( ( "[Application/AWS] Failed to Initialize AWS library\n\n" ) );
//     }

//     aws_connection = (wiced_aws_handle_t)wiced_aws_create_endpoint(&my_publisher_aws_iot_endpoint);
//     if( !aws_connection )
//     {
//         WPRINT_APP_INFO( ( "[Application/AWS] Failed to create AWS connection handle\n\n" ) );
//         return WICED_ERROR;		//return WICED_EPIC_FAIL
//     }

//     my_app_aws_handle = aws_connection;

//     WPRINT_APP_INFO(("[Application/AWS] Opening connection...\n"));
//     ret = wiced_aws_connect(aws_connection);
//     if ( ret != WICED_SUCCESS )
//     {
//         WPRINT_APP_INFO(("[Application/AWS] Connect Failed\r\n"));
//         wiced_rtos_delay_milliseconds( APPLICATION_DELAY_IN_MILLISECONDS * 5 );
//         return WICED_ERROR;
//     }

//     wiced_rtos_delay_milliseconds( APPLICATION_DELAY_IN_MILLISECONDS * 5 );
//     WPRINT_APP_INFO(("[Application/AWS] Subscribing[ Topic %.*s ] ...",(int)strlen(DEMO_AWS_SUBSCRIBER_TOPIC), DEMO_AWS_SUBSCRIBER_TOPIC ) );
//     do
//     {
//         ret = wiced_aws_subscribe( aws_connection, DEMO_AWS_SUBSCRIBER_TOPIC, WICED_AWS_QOS_ATMOST_ONCE);
//         retries++ ;
//     } while ( ( ret != WICED_SUCCESS ) && ( retries < APPLICATION_SUBSCRIBE_RETRY_COUNT ) );
//     if ( ret != WICED_SUCCESS )
//     {
//         WPRINT_APP_INFO((" Failed\n"));
//         is_subscribed = WICED_FALSE;
//     }
//     else
//     {
//         WPRINT_APP_INFO(("Success...\n"));
//         is_subscribed = WICED_TRUE;
//     }

// 	is_connected = WICED_TRUE;
// 	return WICED_SUCCESS;
// }


static void aws_callback( wiced_aws_handle_t aws, wiced_aws_event_type_t event, wiced_aws_callback_data_t* data )
{
    if( !aws || !data || (aws != my_app_aws_handle) )
    return;

    cJSON *root;
    cJSON *left;
    cJSON *right;

    uint8_t leftValue, rightValue;

    switch(event)
    {
        case WICED_AWS_EVENT_CONNECTED:
        {
            WPRINT_APP_INFO(( "AWS connected\n" ));
            if( data->connection.status == WICED_SUCCESS )
            {
                is_connected = WICED_TRUE;
            }
            break;
        }

        case WICED_AWS_EVENT_DISCONNECTED:
        {
            WPRINT_APP_INFO(( "AWS disconnected\n" ));
            if( data->disconnection.status == WICED_SUCCESS )
            {
                is_connected = WICED_FALSE;
            }
            break;
        }

        case WICED_AWS_EVENT_PAYLOAD_RECEIVED:
        {
            WPRINT_APP_INFO( ("[Application/AWS] Payload Received[ Topic: %.*s ]:\n", (int)data->message.topic_length, data->message.topic ) );

        	root = cJSON_Parse((char*) data->message.data);
        	left = cJSON_GetObjectItem(root,"left");
        	right = cJSON_GetObjectItem(root,"right");

            if(left)
            {
                leftValue = (uint8_t) cJSON_GetObjectItem(root,"Left")->valuedouble;
                WPRINT_APP_INFO(("AWS incoming left: %d\n", leftValue));
                leftPumpRequest = leftPumpRequest + (leftValue/10);
            }

            if(right)
            {
                rightValue = (uint8_t) cJSON_GetObjectItem(root,"Right")->valuedouble;
                WPRINT_APP_INFO(("AWS incoming right: %d\n", rightValue));
                rightPumpRequest = rightPumpRequest + (rightValue/10);
            }

            break;
        }

        case WICED_AWS_EVENT_PUBLISHED:
        case WICED_AWS_EVENT_SUBSCRIBED:
        case WICED_AWS_EVENT_UNSUBSCRIBED:
        default:
            WPRINT_APP_INFO(( "AWS some other third thing\n" ));
            break;
    }


}


void awsThread(wiced_thread_arg_t arg)
{
	char topicBuffer[80];

	while(1)
	{
		switch(awsState)
		{
			case AWS_UNINITIALIZED:
                if(awsInitMachine() == AWS_INIT_COMPLETE)
                {
                    awsState = AWS_INITIALIZED;
                }

                // if(aws_start() == WICED_SUCCESS)
                // {
                //     awsState = AWS_INITIALIZED;
                // }
				break;

			case AWS_INITIALIZED:
                if(levelPublishRequest == AWS_PUBLISH_REQUEST)
                {
                    sprintf(topicBuffer, "{\"state\" : {\"reported\" : {\"WaterLevelLeftAWS\" : %d.0, \"WaterLevelRightAWS\" : %d.0}}}", leftLevel, rightLevel);
                    //WPRINT_APP_INFO((topicBuffer));
                    wiced_aws_publish( aws_connection, DEMO_AWS_PUBLISHER_TOPIC, (uint8_t *)topicBuffer, strlen(topicBuffer), WICED_AWS_QOS_ATLEAST_ONCE );
                    levelPublishRequest = NO_PENDING_AWS_PUBREQ;
                }
				break;

            case AWS_NETWORK_LOST:
            
                break;


			case AWS_ERROR:
			default:
				//try and gracefully recover from bad state or error
				break;
		}
		wiced_rtos_delay_milliseconds(AWS_THREAD_DELAY);
	}
}


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
    resource_free_readonly_buffer( &resources_aws_privkey_cer, (const void *)security->certificate );
_fail_client_certificate:
    resource_free_readonly_buffer( &resources_aws_client_cer, (const void *)*root_ca_certificate );
_fail_aws_certificate:
    return WICED_ERROR;
}



//I really don't like the way the init stuff is handled, here is a state machine version
AWS_INIT_RESULT_T awsInitMachine(void)
{
    static AWS_INIT_STATE_T awsInitState = AWS_INIT_BASE;

    wiced_result_t ret;
    AWS_INIT_RESULT_T result = AWS_INIT_ERROR;

    switch(awsInitState)
    {
        case AWS_INIT_BASE:
            /* Disable roaming to other access points */
            wiced_wifi_set_roam_trigger( -99 ); /* -99dBm ie. extremely low signal level */
            ret = get_aws_credentials_from_resources();
            if(ret == WICED_SUCCESS )
            {
                awsInitState = AWS_INIT_NETWORK;
                result = AWS_INIT_IN_PROCESS;
            }
            else
            {
                WPRINT_APP_INFO( ("[Application/AWS] Error fetching credentials from resources\n" ) );
            }
            break;

        case AWS_INIT_NETWORK:
    		ret = wiced_network_up( WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
		    //ret = wiced_network_up(WICED_STA_INTERFACE, WICED_USE_STATIC_IP, &device_static_ip_settings);
            if(ret == WICED_SUCCESS )
            {
                awsInitState = AWS_INIT_AWSLIBRARY;
                result = AWS_INIT_IN_PROCESS;
            }
            else
            {
			    WPRINT_APP_INFO(("Failed to network up\n"));
            }
            break;

        case AWS_INIT_AWSLIBRARY:
            ret = wiced_aws_init( &aws_config , aws_callback );
            if(ret == WICED_SUCCESS)
            {
                awsInitState = AWS_INIT_ENDPOINT;
                result = AWS_INIT_IN_PROCESS;
            }
            else
            {
                WPRINT_APP_INFO( ( "[Application/AWS] Failed to Initialize AWS library\n\n" ) );
            }
            break;

        case AWS_INIT_ENDPOINT:
            aws_connection = (wiced_aws_handle_t)wiced_aws_create_endpoint(&my_publisher_aws_iot_endpoint);
            if(!aws_connection )
            {
                WPRINT_APP_INFO( ( "[Application/AWS] Failed to create AWS connection handle\n\n" ) );
            }
            else
            {
                my_app_aws_handle = aws_connection;
                awsInitState = AWS_INIT_CONNECTION;
                result = AWS_INIT_IN_PROCESS;
            }
            break;

        case AWS_INIT_CONNECTION:
            WPRINT_APP_INFO(("[Application/AWS] Opening connection...\n"));
            ret = wiced_aws_connect(aws_connection);
            if(ret == WICED_SUCCESS)
            {
                awsInitState = AWS_INIT_WAITFORCONNECT;
                result = AWS_INIT_IN_PROCESS;
            }
            else
            {
                WPRINT_APP_INFO(("[Application/AWS] Connect Failed\r\n"));
            }
            break;

        case AWS_INIT_WAITFORCONNECT:
            if(is_connected == WICED_TRUE)
            {
            	awsInitState = AWS_INIT_SUBSCRIPTIONS;
            }
            result = AWS_INIT_IN_PROCESS;            
            break;

        case AWS_INIT_SUBSCRIPTIONS:
            WPRINT_APP_INFO(("[Application/AWS] Subscribing[ Topic %.*s ] ...",(int)strlen(DEMO_AWS_SUBSCRIBER_TOPIC), DEMO_AWS_SUBSCRIBER_TOPIC ) );
            ret = wiced_aws_subscribe( aws_connection, DEMO_AWS_SUBSCRIBER_TOPIC, WICED_AWS_QOS_ATMOST_ONCE);            
            if(ret != WICED_SUCCESS )
            {
                WPRINT_APP_INFO((" Failed\n"));
                is_subscribed = WICED_FALSE;
            }
            else
            {
                WPRINT_APP_INFO(("Success...\n"));
                is_subscribed = WICED_TRUE;
                result = AWS_INIT_COMPLETE;
            }
            break;
            
        default:
            break;
    }
    return result;
}

