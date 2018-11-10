#include "wiced.h"
#include "cy_pdl.h"
#include "cycfg.h"
#include "sound.h"
#include "pumps.h"
#include "cycfg_pins.h"
#include "game.h"
#include "aws.h"
#include "liquidlevel.h"
#include "leduart.h"
#include "game_console.h"
#include "ble_app.h"
#include "globals.h"

/******************************************************
 *               Variable Definitions
 ******************************************************/
static wiced_thread_t gameThreadHandle;
static wiced_thread_t awsThreadHandle;
static wiced_thread_t pumpThreadHandle;
static wiced_thread_t levelThreadHandle;

wiced_queue_t pumpRequestQueueHandle;
wiced_queue_t pumpCommandQueueHandle;
wiced_queue_t gameCommandQueueHandle;
wiced_event_flags_t startFlags;


/******************************************************
 *                      Macros
 ******************************************************/

#define AWS_THREAD_PRIORITY     6
#define LEVEL_THREAD_PRIORITY   6
#define PUMP_THREAD_PRIORITY    6
#define GAME_THREAD_PRIORITY    6

#define AWS_STACK_SIZE 6144
#define GAME_STACK_SIZE 4096
#define LEVEL_STACK_SIZE 1024
#define PUMP_STACK_SIZE 1024

/* The queue messages will be 4 bytes each (a 32 bit integer) */
#define QUEUE_SIZE			(10)

void application_start(void)
{

	wiced_init();

	WPRINT_APP_INFO(("Starting Game Controller\n"));
	initGameConsole();
	ledUARTinit();          //this uart is handled by interrupt, no thread to init it in
	initAudioHW();          //audio is handled by DMA and PWM, no thread to initialize those

	/* enable interrupts */
	__enable_irq();

	//initialize the pump queues
	wiced_rtos_init_queue(&pumpRequestQueueHandle, "pumpRequestQueue", sizeof(pumps_speed_request_t), QUEUE_SIZE); /* Setup the queue for pump run requests  */
	wiced_rtos_init_queue(&pumpCommandQueueHandle, "pumpCommandQueue", sizeof(pumps_command_request_t), QUEUE_SIZE); /* Setup the queue for pump commands */
	wiced_rtos_init_queue(&gameCommandQueueHandle, "gameCommandQueue", sizeof(pumps_command_request_t), QUEUE_SIZE); /* Setup the queue for pump commands */
	wiced_rtos_init_event_flags(&startFlags);

	startBle();
	wiced_rtos_delay_milliseconds(2000);


	//start the various threads
	wiced_rtos_create_thread(&awsThreadHandle, AWS_THREAD_PRIORITY, "awsThread", awsThread, AWS_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&levelThreadHandle, LEVEL_THREAD_PRIORITY, "levelThread", levelThread, LEVEL_STACK_SIZE, NULL);
	wiced_rtos_create_thread(&pumpThreadHandle, PUMP_THREAD_PRIORITY, "pumpThread", pumpsThread, PUMP_STACK_SIZE, NULL);
	uint32_t tempFlags;
	wiced_rtos_wait_for_event_flags(&startFlags,(uint32_t)(START_FLAG_PUMP|START_FLAG_LEVEL),&tempFlags,WICED_FALSE,WAIT_FOR_ALL_EVENTS,WICED_WAIT_FOREVER);
	wiced_rtos_create_thread(&gameThreadHandle, GAME_THREAD_PRIORITY, "gameThread", gameThread, GAME_STACK_SIZE, NULL);

	while(1)
	{
		Cy_GPIO_Inv(GREEN_LED_PORT, GREEN_LED_PIN);
		wiced_rtos_delay_milliseconds(500);
	}
}
