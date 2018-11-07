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
#include "bt.h"
#include "pumps.h"
#include "cy_pdl.h"


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
static int help_console_cmd( int argc, char *argv[] );
static int levels_console_cmd( int argc, char *argv[] );
static int start_console_cmd( int argc, char *argv[] );
static int pause_console_cmd( int argc, char *argv[] );
static int resume_console_cmd( int argc, char *argv[] );
static int abort_console_cmd( int argc, char *argv[] );
static int reset_console_cmd( int argc, char *argv[] );
static int leftpump_console_cmd( int argc, char *argv[] );
static int rightpump_console_cmd( int argc, char *argv[] );
static int wifion_console_cmd( int argc, char *argv[] );
static int wifioff_console_cmd( int argc, char *argv[] );
static int bleon_console_cmd( int argc, char *argv[] );
static int bleoff_console_cmd( int argc, char *argv[] );
static int pumpenable_console_cmd( int argc, char *argv[] );
static int pumpdisable_console_cmd( int argc, char *argv[] );

#define GAME_CONSOLE_COMMANDS \
    { (char*) "status",  status_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Print game status"   }, \
    { (char*) "gamehelp",  help_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Print game command list"   }, \
    { (char*) "levels", levels_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Read liquid levels"   }, \
    { (char*) "start", start_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Start game"   }, \
    { (char*) "pause", pause_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Pause game"   }, \
    { (char*) "resume", resume_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Resume game"   }, \
    { (char*) "abort", abort_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Abort game"   }, \
    { (char*) "reset", reset_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Reset game"   }, \
    { (char*) "leftpump", leftpump_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Kick left pump"   }, \
    { (char*) "rightpump", rightpump_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Kick right pump"   }, \
    { (char*) "wifion", wifion_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Enable wifi and connect"   }, \
    { (char*) "wifioff", wifioff_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Disconnect and disable wifi"   }, \
    { (char*) "bleon", bleon_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Enable BLE"   }, \
    { (char*) "bleoff", bleoff_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Disable BLE"   }, \
    { (char*) "enablepumps", pumpenable_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Enable pumps"   }, \
    { (char*) "disablepumps", pumpdisable_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Disable pumps"   }, \

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
    return ERR_CMD_OK;
}

static int help_console_cmd( int argc, char *argv[] )
{
    consolePrintHelp();
    return ERR_CMD_OK;
}

static int levels_console_cmd( int argc, char *argv[] )
{
    reportLevels();
    return ERR_CMD_OK;
}

static int start_console_cmd( int argc, char *argv[] )
{
    gameStateRequest = 	REQUEST_START;
    return ERR_CMD_OK;
}

static int pause_console_cmd( int argc, char *argv[] )
{
    gameStateRequest = 	REQUEST_PAUSE;
    return ERR_CMD_OK;
}

static int resume_console_cmd( int argc, char *argv[] )
{
    gameStateRequest = REQUEST_RESUME;
    return ERR_CMD_OK;
}

static int abort_console_cmd( int argc, char *argv[] )
{
    gameStateRequest = REQUEST_ABORT;
    return ERR_CMD_OK;
}

static int reset_console_cmd( int argc, char *argv[] )
{
    gameStateRequest = REQUEST_RESET;
    return ERR_CMD_OK;
}

static int leftpump_console_cmd( int argc, char *argv[] )
{
    if(wiced_rtos_is_queue_full(&pumpRequestQueueHandle) != WICED_SUCCESS)     //this means if the queue isn't full
    {
        PUMP_REQUEST_T pumpRequest;

        pumpRequest.pumpBytes.leftPumpRequest = 100;
        pumpRequest.pumpBytes.rightPumpRequest = 0;
        pumpRequest.pumpBytes.dummya = 0;
        pumpRequest.pumpBytes.dummyb = 0;

        wiced_rtos_push_to_queue(&pumpRequestQueueHandle, &pumpRequest.pumpWord, WICED_NO_WAIT); /* Push value onto queue*/
    }
    return ERR_CMD_OK;
}

static int rightpump_console_cmd( int argc, char *argv[] )
{
    if(wiced_rtos_is_queue_full(&pumpRequestQueueHandle) != WICED_SUCCESS)     //this means if the queue isn't full
    {
        PUMP_REQUEST_T pumpRequest;

        pumpRequest.pumpBytes.leftPumpRequest = 0;
        pumpRequest.pumpBytes.rightPumpRequest = 100;
        pumpRequest.pumpBytes.dummya = 0;
        pumpRequest.pumpBytes.dummyb = 0;

        wiced_rtos_push_to_queue(&pumpRequestQueueHandle, &pumpRequest.pumpWord, WICED_NO_WAIT); /* Push value onto queue*/
    }
    return ERR_CMD_OK;
}

static int wifion_console_cmd( int argc, char *argv[] )
{
    //awsEnableStatus = AWS_ENABLE;
    return ERR_CMD_OK;
}

static int wifioff_console_cmd( int argc, char *argv[] )
{
    //awsEnableStatus = AWS_DISABLE;
    return ERR_CMD_OK;
}

static int bleon_console_cmd( int argc, char *argv[] )
{
    //btEnableStatus = BT_ENABLE;
    return ERR_CMD_OK;
}

static int bleoff_console_cmd( int argc, char *argv[] )
{
    //btEnableStatus = BT_DISABLE;
    return ERR_CMD_OK;
}

static int pumpenable_console_cmd( int argc, char *argv[] )
{
    uint32_t pumpCommand;
	pumpCommand = (uint32_t) PUMPS_ENABLED;
	wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/    
    return ERR_CMD_OK;
}

static int pumpdisable_console_cmd( int argc, char *argv[] )
{
    uint32_t pumpCommand;
	pumpCommand = (uint32_t) PUMPS_DISABLED;
	wiced_rtos_push_to_queue(&pumpCommandQueueHandle, &pumpCommand, WICED_NO_WAIT); /* Push value onto queue*/    
    return ERR_CMD_OK;
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
}

// void consolePrintSystick(void)
// {
// 	uint32_t systicks = 0x00;     //tx_get_time();
//     WPRINT_APP_INFO(("System tick count: %lu\n", systicks));
// }

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
    getGameStateString(stateString);
    WPRINT_APP_INFO(("Game master state: %s\n", stateString));
}

void consolePrintHelp(void)
{
    WPRINT_APP_INFO(("*********************************************\n"));
    WPRINT_APP_INFO(("Available game commands:\n"));
    WPRINT_APP_INFO(("     status     get game status\n"));
    WPRINT_APP_INFO(("     version    get firmware version\n"));
    WPRINT_APP_INFO(("     gamehelp   print this command list\n"));
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
   if(leftLevel > rightLevel)
   {
       WPRINT_APP_INFO(( "    Left team wins!\n"));
   }
   else
   {
       WPRINT_APP_INFO(( "    Right team wins!\n"));
   }
    consolePrintStatus();    
}

