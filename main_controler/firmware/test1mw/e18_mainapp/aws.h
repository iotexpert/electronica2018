

#include "wiced.h"

#ifndef GAME_AWS_H
#define GAME_AWS_H

#define DEMO_AWS_PUBLISHER_TOPIC "$aws/things/Electronica2018/shadow/update"
#define DEMO_AWS_SUBSCRIBER_TOPIC "PumpAWS"

typedef enum{
    NO_PENDING_AWS_PUBREQ,
    AWS_PUBLISH_REQUEST
}AWS_PUBREQ_T;

extern AWS_PUBREQ_T levelPublishRequest;

#define AWS_THREAD_DELAY	250

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



extern void awsThread(wiced_thread_arg_t arg);

#endif
