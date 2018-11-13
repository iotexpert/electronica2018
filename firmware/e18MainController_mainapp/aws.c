#include "wiced.h"
#include "aws_common.h"
#include "wiced_aws.h"
#include "aws.h"
#include "resources.h"
#include "game.h"
#include "liquidlevel.h"
#include "pumps.h"
#include "globals.h"


#include "globals.h"
#include "wiced.h"
#include "wiced_aws.h"
#include "aws_common.h"
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
#define SUBSCRIBE_PUBLISH_TOPIC                          "PumpAWS"
#define SHADOW_UPDATE_SUBSCRIBE_TOPIC				"$aws/things/Electronica2018/shadow/update/accepted"

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

/* Water level % pulled from AWS */
static uint8_t waterLeft  = 0;
static uint8_t waterRight = 0;

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
        return;


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
            WPRINT_APP_INFO( ( "Water Left: %d\t Water Right: %d\n", left, right) );

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
    char msg[18]; /* This will hold the JSON message to be published */
    char thingName[] = "remote001122334455"; /* This gets replaced with the MAC address */

    wiced_wifi_get_mac_address(&mac);

    wiced_rtos_init_semaphore(&aws_semaphore_handle);

    /* Set up WiFi Screen */

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
		wiced_aws_subscribe( aws_connection, SUBSCRIBE_PUBLISH_TOPIC,   WICED_AWS_QOS_ATMOST_ONCE);

		/* Display message */

		while ( 1 ) /* Loop to wait for swipe messages and publish to AWS */
		{
			wiced_rtos_delay_milliseconds(200);
#if 0
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
#endif

		} /* End of inner while(1) loop that waits for swipe values and publishes them */

		WPRINT_APP_INFO(("[Application/AWS] Closing connection...\r\n"));
		wiced_aws_disconnect( aws_connection );

		WPRINT_APP_INFO(("[Application/AWS] Deinitializing AWS library...\r\n"));
		ret = wiced_aws_deinit( );

	} /* End of outer while(1) that will reconnect if the connection is lost */
}


#if 0

#define DEMO_AWS_PUBLISHER_TOPIC "$aws/things/Electronica2018/shadow/update"
#define DEMO_AWS_SUBSCRIBER_TOPIC "PumpAWS"

#define AWS_THREAD_DELAY	250

#define AWS_PUBLISH_LEVELS_ON_DELTA     //if defined, water levels on published when a change is detected, 
//otherwise published every AWS thread iteration

typedef enum{
	AWS_UNINITIALIZED,
	AWS_INITIALIZED,
	AWS_NETWORK_LOST,
	AWS_ERROR
}AWS_STATE_T;

typedef enum{
	AWS_INIT_BASE,
	AWS_INIT_NETWORK,
	AWS_INIT_AWSLIBRARY,
	AWS_INIT_CONNECTION,
	AWS_INIT_ENDPOINT,
	AWS_INIT_WAITFORCONNECT,
	AWS_INIT_SUBSCRIPTIONS
}AWS_INIT_STATE_T;

typedef enum{
	AWS_INIT_ERROR,
	AWS_INIT_IN_PROCESS,
	AWS_INIT_COMPLETE
}AWS_INIT_RESULT_T;


/******************************************************
 *               Variable Definitions
 ******************************************************/

static wiced_bool_t       is_connected = WICED_FALSE;
static wiced_aws_handle_t my_app_aws_handle;
static wiced_bool_t is_subscribed = WICED_FALSE;
static wiced_aws_handle_t aws_connection = 0;
static AWS_STATE_T awsState = AWS_UNINITIALIZED;

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


#define PUBLISHER_CERTIFICATES_MAX_SIZE            (0x7fffffff)

//function prototypes

static void aws_callback(wiced_aws_handle_t aws, wiced_aws_event_type_t event, wiced_aws_callback_data_t* data);
static wiced_result_t get_aws_credentials_from_resources(void);
static AWS_INIT_RESULT_T awsInitMachine(void);


//code
static void aws_callback( wiced_aws_handle_t aws, wiced_aws_event_type_t event, wiced_aws_callback_data_t* data )
{
	if( !aws || !data || (aws != my_app_aws_handle) )
		return;

	cJSON *root;
	cJSON *left;
	cJSON *right;

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

		pumpsSendValues(leftValue,rightValue);

		break;
	}

	case WICED_AWS_EVENT_PUBLISHED:
	case WICED_AWS_EVENT_SUBSCRIBED:
	case WICED_AWS_EVENT_UNSUBSCRIBED:
	default:
		WPRINT_APP_INFO(( "AWS default event\n" ));
		break;
	}


}


void awsThread(wiced_thread_arg_t arg)
{
	static uint8_t previousLeftLevel = 255;         //set outside normal range 255 so it will trigger update on first connected iteration
	static uint8_t previousRightLevel = 255;         //set outside normal range 255 so it will trigger update on first connected iteration

	WPRINT_APP_INFO(("Starting AWS\n"));

	// Wait for the BLE to Start
	uint32_t tempFlags;
	wiced_rtos_wait_for_event_flags(&startFlags,(uint32_t)(TASK_FLAG_BLE),&tempFlags,WICED_FALSE,WAIT_FOR_ALL_EVENTS,WICED_WAIT_FOREVER);
	wiced_rtos_set_event_flags(	&startFlags,	TASK_FLAG_AWS);

	AWS_INIT_RESULT_T awsInitResult;
	while(1)
	{

		switch(awsState)
		{
		case AWS_UNINITIALIZED:
			awsInitResult = awsInitMachine();
			if(awsInitResult == AWS_INIT_COMPLETE)
			{
				awsState = AWS_INITIALIZED;
			}
			if(awsInitResult == AWS_INIT_ERROR)
			{
				return; // return and kill the thread
			}
			break;

		case AWS_INITIALIZED:
			if((previousLeftLevel != levelGetLeft()) || (previousRightLevel != levelGetRight()))
			{
				char topicBuffer[80];
				sprintf(topicBuffer, "{\"state\" : {\"reported\" : {\"WaterLevelLeftAWS\" : %d.0, \"WaterLevelRightAWS\" : %d.0}}}", (int)levelGetLeft(), (int)levelGetRight());
				wiced_aws_publish( aws_connection, DEMO_AWS_PUBLISHER_TOPIC, (uint8_t *)topicBuffer, strlen(topicBuffer), WICED_AWS_QOS_ATLEAST_ONCE );
				previousLeftLevel = levelGetLeft();
				previousRightLevel = levelGetRight();
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
	int retryCount=0;

	WPRINT_APP_INFO(("awsInitMachine\n"));

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
		WPRINT_APP_INFO(("Attempting WICED network up\n"));
		do {

			ret = wiced_network_up( WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL );
			retryCount += 1;
		} while(ret != WICED_SUCCESS && retryCount < 5);


		if(ret == WICED_SUCCESS )
		{
			awsInitState = AWS_INIT_AWSLIBRARY;
			result = AWS_INIT_IN_PROCESS;
		}
		else
		{
			WPRINT_APP_INFO(("Failed to network up\n"));
			return AWS_INIT_ERROR;
		}

		awsInitState = AWS_INIT_AWSLIBRARY;
		result = AWS_INIT_IN_PROCESS;

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
		do {
			int retryCount = 0;
		WPRINT_APP_INFO(("[Application/AWS] Subscribing[ Topic %.*s ] ...",(int)strlen(DEMO_AWS_SUBSCRIBER_TOPIC), DEMO_AWS_SUBSCRIBER_TOPIC ) );
		ret = wiced_aws_subscribe( aws_connection, DEMO_AWS_SUBSCRIBER_TOPIC, WICED_AWS_QOS_ATMOST_ONCE);
		retryCount += 1;
			if(ret != WICED_SUCCESS)
				wiced_rtos_delay_milliseconds(1000);
		} while(ret != WICED_SUCCESS && retryCount<10);
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

	}
	return result;
}

#endif
