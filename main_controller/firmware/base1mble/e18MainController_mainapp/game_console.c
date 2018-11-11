/*
 * command_console.c
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#include "wiced.h"
#include "game.h"
#include "game_console.h"
#include "string.h"
#include "stdio.h"
#include "cycfg_peripherals.h"
#include "liquidlevel.h"
#include "command_console.h"
#include "aws.h"
#include "pumps.h"
#include "cy_pdl.h"
#include "globals.h"


//defines needed for wiced console
#define GAME_COMMAND_HISTORY_LENGTH  (10)
#define MAX_GAME_COMMAND_LENGTH      (85)
#define MAX_ASCII_VALUE               0x7e
#define ROLL_OVER_ASCII_VALUE         0x2f

//variables
static char game_command_buffer[MAX_GAME_COMMAND_LENGTH];
static char game_command_history_buffer[MAX_GAME_COMMAND_LENGTH * GAME_COMMAND_HISTORY_LENGTH];
cy_stc_scb_uart_context_t consoleUARTcontext;

//function prototypes
static int status_console_cmd( int argc, char *argv[] );
static int levels_console_cmd( int argc, char *argv[] );
static int start_console_cmd( int argc, char *argv[] );
static int stop_console_cmd( int argc, char *argv[] );
static int pause_console_cmd( int argc, char *argv[] );
static int resume_console_cmd( int argc, char *argv[] );
static int leftpump_console_cmd( int argc, char *argv[] );
static int rightpump_console_cmd( int argc, char *argv[] );
static int wifion_console_cmd( int argc, char *argv[] );
static int wifioff_console_cmd( int argc, char *argv[] );
static int bleon_console_cmd( int argc, char *argv[] );
static int bleoff_console_cmd( int argc, char *argv[] );
static int pumpenable_console_cmd( int argc, char *argv[] );
static int pumpdisable_console_cmd( int argc, char *argv[] );
static int pumpDecay_console_cmd( int argc, char *argv[] );
static int consoleThreads_cmd( int argc, char *argv[] );


#define GAME_CONSOLE_COMMANDS \
    { (char*) "status",  status_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Print game status"   }, \
    { (char*) "levels", levels_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Read liquid levels"   }, \
    { (char*) "start", start_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Start game"   }, \
    { (char*) "stop", stop_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Stop game"   }, \
    { (char*) "pause", pause_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Pause game"   }, \
    { (char*) "resume", resume_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Resume game"   }, \
    { (char*) "leftpump", leftpump_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Kick left pump"   }, \
    { (char*) "rightpump", rightpump_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Kick right pump"   }, \
    { (char*) "wifion", wifion_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Enable wifi and connect"   }, \
    { (char*) "wifioff", wifioff_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Disconnect and disable wifi"   }, \
    { (char*) "bleon", bleon_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Enable BLE"   }, \
    { (char*) "bleoff", bleoff_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Disable BLE"   }, \
    { (char*) "enablepumps", pumpenable_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Enable pumps"   }, \
    { (char*) "disablepumps", pumpdisable_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Disable pumps"   }, \
    { (char*) "decay", pumpDecay_console_cmd,      1, NULL, NULL, (char *)"", (char *)"Disable pumps"   }, \
    { (char*) "threads", consoleThreads_cmd,      0, NULL, NULL, (char *)"", (char *)"Thread status information"   }, \


const command_t game_console_command_table[] =
{
    GAME_CONSOLE_COMMANDS
    CMD_TABLE_END
};


//function prototypes
void consolePrintVersion(void);
void consolePrintGameState(void);

//code
static int status_console_cmd( int argc, char *argv[] )
{
    consolePrintStatus();
    return 0;
}


static int levels_console_cmd( int argc, char *argv[] )
{
    reportLevels();
    return 0;
}

static int start_console_cmd( int argc, char *argv[] )
{
	gameStateRequest(GAME_START);
	return 0;
}

static int pause_console_cmd( int argc, char *argv[] )
{
	gameStateRequest(GAME_PAUSE);
    return 0;
}

static int resume_console_cmd( int argc, char *argv[] )
{
	gameStateRequest(GAME_RUNNING);
	return 0;
}

static int stop_console_cmd( int argc, char *argv[] )
{
	gameStateRequest(GAME_IDLE);
	return 0;
}

static int leftpump_console_cmd( int argc, char *argv[] )
{
	pumpsSendValues(100,0);
	return 0;
}

static int rightpump_console_cmd( int argc, char *argv[] )
{
	pumpsSendValues(0,100);
	return 0;
}

static int wifion_console_cmd( int argc, char *argv[] )
{
    //awsEnableStatus = AWS_ENABLE;
    return 0;
}

static int wifioff_console_cmd( int argc, char *argv[] )
{
    //awsEnableStatus = AWS_DISABLE;
    return 0;
}

static int bleon_console_cmd( int argc, char *argv[] )
{
    //btEnableStatus = BT_ENABLE;
    return 0;
}

static int bleoff_console_cmd( int argc, char *argv[] )
{
    //btEnableStatus = BT_DISABLE;
    return 0;
}

static int pumpenable_console_cmd( int argc, char *argv[] )
{
    	pumpsSendEnable();
    return 0;
}

static int pumpdisable_console_cmd( int argc, char *argv[] )
{
    pumpsSendDisable();
    return 0;
}

static int pumpDecay_console_cmd( int argc, char *argv[] )
{
	int val;
	sscanf(argv[1],"%d",&val);

	pumpsSendDecay((uint32_t)val);
    return 0;
}


uint32_t maxStackUsage(TX_THREAD *thread)
{
	uint8_t *end =   thread->tx_thread_stack_end;
	uint8_t *start = thread->tx_thread_stack_start;
	while(start < end)
	{
		if(*start != 0xEF)
		{
			return end-start;
		}
		start++;
	}
	return 0;
}

void threadInfo(TX_THREAD *thread)
{

	WPRINT_APP_INFO(("%13.13s\t",thread->tx_thread_name));
	WPRINT_APP_INFO(("%02d\t",thread->tx_thread_priority));
	WPRINT_APP_INFO(("%d\t",(int)thread->tx_thread_run_count));
	WPRINT_APP_INFO(("%d\t",(int)thread->tx_thread_stack_size));

	WPRINT_APP_INFO(("%d\t",(int)maxStackUsage(thread)));

	switch(thread->tx_thread_state)
	{
	case 0x00:
		WPRINT_APP_INFO(("TX_READY"));
		break;

	case 0x01:
		WPRINT_APP_INFO(("TX_COMPLETED"));
		break;

	case 0x02:
		WPRINT_APP_INFO(("TX_TERMINATED"));
		break;

	case 0x03:
		WPRINT_APP_INFO(("TX_SUSPENDED"));
		break;

	case 0x04:
		WPRINT_APP_INFO(("TX_SLEEP"));
		break;

	case 0x05:
		WPRINT_APP_INFO(("TX_QUEUE_SUSP"));
		break;

	case 0x06:
		WPRINT_APP_INFO(("TX_SEMAPHORE_SUSP"));
		break;

	case 0x07:
		WPRINT_APP_INFO(("TX_EVENT_FLAG"));
		break;

	case 0x08:
		WPRINT_APP_INFO(("TX_BLOCK_MEMORY"));
		break;

	case 0x09:
		WPRINT_APP_INFO(("TX_BYTE_MEMORY"));
		break;

	case 0x0D:
		WPRINT_APP_INFO(("TX_MUTEX_SUSP"));
		break;
	}

	WPRINT_APP_INFO(("\n"));
}

void threadList(wiced_thread_t *thread)
{
	TX_THREAD *ptr = &thread->handle;

	do {
		threadInfo(ptr);
		ptr = ptr->tx_thread_created_previous;

	} while(ptr != &thread->handle);

}

static int consoleThreads_cmd( int argc, char *argv[] )
{
	WPRINT_APP_INFO(("Name\t\tPri\tRun #\tStack\tUsage\tStatus\n"));
	threadList(&gameThreadHandle);

#if 0
	threadInfo(&gameThreadHandle);
	threadInfo(&awsThreadHandle);
	threadInfo(&pumpThreadHandle);
	threadInfo(&levelThreadHandle);
#endif
	return 0;
}






void initGameConsole(void)
{
    wiced_result_t result;
    result = command_console_init(STDIO_UART, sizeof(game_command_buffer), game_command_buffer,
                GAME_COMMAND_HISTORY_LENGTH, game_command_history_buffer, " ");
    if (result != WICED_SUCCESS)
    {
        WPRINT_APP_INFO(("Error starting the command console\r\n"));
    }
    console_add_cmd_table(game_console_command_table);
}

void consolePrintWelcome(void)
{
    WPRINT_APP_INFO(("*********************************************\n"));
    WPRINT_APP_INFO(("Shall we play a game?\n"));
    consolePrintVersion();
    WPRINT_APP_INFO(("*********************************************\n"));
}


void consolePrintVersion(void)
{
    WPRINT_APP_INFO(("Game demo FW version: %c.%c\n", FW_VERSION_MAJOR, FW_VERSION_MINOR));
}

void consolePrintStatus(void)
{
    WPRINT_APP_INFO(("Game status:\n"));
    consolePrintGameState();
    reportLevels();
}

void consolePrintGameState(void)
{
    char stateString[40];
    gameGetString(stateString);
    WPRINT_APP_INFO(("Game master state: %s\n", stateString));
}

void consolePrintHelp(void)
{
    WPRINT_APP_INFO(("*********************************************\n"));
    WPRINT_APP_INFO(("Available game commands:\n"));
    WPRINT_APP_INFO(("     status     get game status\n"));
    WPRINT_APP_INFO(("     version    get firmware version\n"));
    WPRINT_APP_INFO(("     levels     get liquid levels\n"));
    WPRINT_APP_INFO(("     start      start/resume game\n"));
    WPRINT_APP_INFO(("     pause      pause game\n"));
    WPRINT_APP_INFO(("     reset      reset game after win\n"));
    WPRINT_APP_INFO(("     leftpump   add to left pump run speed\n"));
    WPRINT_APP_INFO(("     rightpump  add to left pump run speed\n"));
    WPRINT_APP_INFO(("     abort      abort game and reset system\n"));
    WPRINT_APP_INFO(("     wifion     enable wifi\n"));
    WPRINT_APP_INFO(("     wifioff    disable wifi\n"));
    WPRINT_APP_INFO(("     bleon       enable ble\n"));
    WPRINT_APP_INFO(("     bleoff      disable ble\n"));
}

void consolePrintWin(void)
{
    WPRINT_APP_INFO(("*********************************************\n"));
    WPRINT_APP_INFO((" GAME WIN\n"));
   if(levelGetLeft() > levelGetRight())
   {
       WPRINT_APP_INFO(( "    Left team wins!\n"));
   }
   else
   {
       WPRINT_APP_INFO(( "    Right team wins!\n"));
   }
    consolePrintStatus();    
}

