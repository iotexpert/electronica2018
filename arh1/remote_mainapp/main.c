
#include "wiced.h"
#include "GoBleThread.h"
#include "awsThread.h"

wiced_thread_t awsThreadHandle;
wiced_thread_t subscriberThreadHandle;

void application_start()
{
    wiced_init( );
    WPRINT_APP_INFO(("System Started\n"));
    GoBleThread_start();
    wiced_rtos_create_thread(&awsThreadHandle, 7, "awsThread", awsThread, 4096, 0);
}
