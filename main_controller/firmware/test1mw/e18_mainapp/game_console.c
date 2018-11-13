/*
 * command_console.c
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#include "game.h"
#include "game_console.h"
#include "string.h"
#include "stdio.h"
#include "cycfg_peripherals.h"
#include "liquidlevel.h"
#include "command_console.h"


//#define CONSOLE_TXBUFFER_SIZE   2048
//#define CONSOLE_RXBUFFER_SIZE   256
//#define COMMAND_BUFFER_SIZE 128


#define GAME_COMMAND_HISTORY_LENGTH  (10)
#define MAX_GAME_COMMAND_LENGTH              (85)
#define MAX_ASCII_VALUE                              0x7e
#define ROLL_OVER_ASCII_VALUE                        0x2f



// cy_stc_scb_uart_context_t consoleUARTcontext;

//uint8_t rxBuffer[CONSOLE_RXBUFFER_SIZE];
//uint8_t* rxEndPtr = rxBuffer;
//uint8_t* rxSendPtr = rxBuffer;
//uint8_t* rxReadPtr = rxBuffer;
//uint8_t commandBuffer[COMMAND_BUFFER_SIZE];

//uint8_t txBuffer[CONSOLE_TXBUFFER_SIZE];
//uint8_t* txEndPtr = txBuffer;
//uint8_t* txSendPtr = txBuffer;
//uint8_t consoleTXenabled;
//static uint8_t txWriteLock = 0;

extern uint8_t leftSpeed;
extern uint8_t rightSpeed;

//INCOMING_CMD_T incomingCommand = NO_INCOMING_CMD;

static char game_command_buffer[MAX_GAME_COMMAND_LENGTH];
static char game_command_history_buffer[MAX_GAME_COMMAND_LENGTH * GAME_COMMAND_HISTORY_LENGTH];

void consolePrintStatus(void);
void consolePrintWin(void);
void consolePrintLevels(void);
void consolePrintCRLF(uint8_t numNewlines);
GAME_COMMAND_T determineCommand(char* incomingCommandBuffer);
void handleCommand(GAME_COMMAND_T command);

static int status_console_cmd( int argc, char *argv[] );
static int help_console_cmd( int argc, char *argv[] );
static int levels_console_cmd( int argc, char *argv[] );
static int start_console_cmd( int argc, char *argv[] );
static int pause_console_cmd( int argc, char *argv[] );
static int resume_console_cmd( int argc, char *argv[] );
static int abort_console_cmd( int argc, char *argv[] );
static int reset_console_cmd( int argc, char *argv[] );



//only needed this for non-rtos initial hardware test version, wiced sdk controls this uart
// void initConsoleUART(void)
// {
//     kitprog linked UART
//     Cy_SCB_UART_Init(consoleUART_HW, &consoleUART_config, &consoleUARTcontext);
//     Cy_SCB_UART_Enable(consoleUART_HW);
//     Cy_SysInt_Init(&consoleUartIntrCfg, &consoleUARTinterrupt);
//     NVIC_EnableIRQ(consoleUartIntrCfg.intrSrc);
// }



// uint16_t extractCommand(void)
// {
//	 uint16 numIncomingBytes = 0;
//	 while(rxReadPtr != rxEndPtr)
//	 {
//		 commandBuffer[numIncomingBytes] = *rxReadPtr;
//		 rxReadPtr++;
//		 if(rxReadPtr > rxBuffer + CONSOLE_RXBUFFER_SIZE) rxReadPtr = rxBuffer;
//		 numIncomingBytes++;
//		 if(numIncomingBytes == sizeof(commandBuffer))
//		 {
//			 numIncomingBytes = 0;
//			 break;					//I usually don't like to this, but break due to error
//		 }
//	 }
//
//	 incomingCommand = NO_INCOMING_CMD;
//	 return numIncomingBytes;
// }


//adding in wiced command console
#define GAME_CONSOLE_COMMANDS \
    { (char*) "status",  status_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Print game status"   }, \
    { (char*) "gamehelp",  help_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Print game command list"   }, \
    { (char*) "levels", levels_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Read liquid levels"   }, \
    { (char*) "start", start_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Start game"   }, \
    { (char*) "pause", pause_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Pause game"   }, \
    { (char*) "resume", resume_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Resume game"   }, \
    { (char*) "abort", abort_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Abort game"   }, \
    { (char*) "reset", reset_console_cmd,      0, NULL, NULL, (char *)"", (char *)"Reset game"   }, \


const command_t game_console_command_table[] =
{
    GAME_CONSOLE_COMMANDS
    CMD_TABLE_END
};

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
    consolePrintLevels();
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





void consolePrintCRLF(uint8_t numNewlines)
{
	uint8_t index;
	for(index = 0; index < numNewlines; index++)
	{
	    WPRINT_APP_INFO(("\n"));
	}
}

void consolePrintWelcome(void)
{
    WPRINT_APP_INFO(("*********************************************\n"));
    WPRINT_APP_INFO(("Shall we play a game?\n"));
    consolePrintVersion();
    consolePrintCRLF(1);
    consolePrintSystick();
    consolePrintCRLF(2);
}


void consolePrintSystick(void)
{
    WPRINT_APP_INFO(("System tick count: %lu\n", systicks));
}


void consolePrintVersion(void)
{
    WPRINT_APP_INFO(("Game demo FW version: %c.%c\n", FW_VERSION_MAJOR, FW_VERSION_MINOR));
}


void consolePrintStatus(void)
{
    WPRINT_APP_INFO(("Game status:\n"));
    consolePrintGameState();
    consolePrintLevels();
    consolePrintSystick();
}

void consolePrintGameState(void)
{
    char stateString[40];
    getGameStateString(stateString);
    WPRINT_APP_INFO(("Game master state: %s\n", stateString));
}


void consolePrintLevels(void)
{
    WPRINT_APP_INFO(("Left liquid level: %u\n", leftLevel));
    WPRINT_APP_INFO(("Right liquid level: %u\n", rightLevel));
}

extern void consolePrintPumpSpeed(void)
{
    WPRINT_APP_INFO(("Left pump: %u  Right pump: %u\n", leftSpeed, rightSpeed));
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
    WPRINT_APP_INFO(("     reset      reset game after win"));
    WPRINT_APP_INFO(("     leftpump   add to left pump run speed\n"));
    WPRINT_APP_INFO(("     rightpump  add to left pump run speed\n"));
    WPRINT_APP_INFO(("     abort      abort game and reset system\n"));
    WPRINT_APP_INFO(("     wifion     enable wifi\n"));
    WPRINT_APP_INFO(("     wifioff    disable wifi\n"));
    WPRINT_APP_INFO(("     bton       enable bt\n"));
    WPRINT_APP_INFO(("     btoff      disable bt\n"));
    //WPRINT_APP_INFO(("     demo1      run demo game one\n"));
    //WPRINT_APP_INFO(("     demo2      run demo game two\n"));
}


void consolePrintGameAbort(void)
{
    WPRINT_APP_INFO(("*********************************************\n"));
    WPRINT_APP_INFO((" GAME ABORT\n"));
    consolePrintStatus();    
}



//print winning info
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

//print error (could add ERROR_TYPE argument)
void consolePrintError(void)
{
    WPRINT_APP_INFO(("Unknown command\n"));
}

//void handleIncomingCommand(void)
//{
//	if(extractCommand() == 0)
//	{
//		consolePrintError();
//	}
//	else
//	{
//		GAME_COMMAND_T command = determineCommand((char*) commandBuffer);
//		handleCommand(command);
//	}
//}

//preference is for single return statement in function, however
//for a command interpreter like this, there is no sense in wasting
//cycles once a command has been found...easy to debate/change
GAME_COMMAND_T determineCommand(char* incomingCommandBuffer)
{
    GAME_COMMAND_T returnValue = ERROR_CMD;
    if(!memcmp(incomingCommandBuffer, "status", 0x06)) return STATUS_CMD;
    if(!memcmp(incomingCommandBuffer, "version", 0x07)) return VERSION_CMD;
    if(!memcmp(incomingCommandBuffer, "help", 0x04)) return HELP_CMD;
    if(!memcmp(incomingCommandBuffer, "?", 0x01)) return HELP_CMD;
    if(!memcmp(incomingCommandBuffer, "levels", 0x06)) return GETLEVEL_CMD;
    if(!memcmp(incomingCommandBuffer, "start", 0x05)) return START_CMD;
    if(!memcmp(incomingCommandBuffer, "pause", 0x05)) return PAUSE_CMD;
    if(!memcmp(incomingCommandBuffer, "resume", 0x06)) return RESUME_CMD;
    if(!memcmp(incomingCommandBuffer, "leftpump", 0x08)) return LEFT_PUMP_CMD;
    if(!memcmp(incomingCommandBuffer, "rightpump", 0x09)) return RIGHT_PUMP_CMD;
    if(!memcmp(incomingCommandBuffer, "abort", 0x05)) return ABORT_CMD;
    if(!memcmp(incomingCommandBuffer, "wifion", 0x06)) return ENABLEWIFI_CMD;
    if(!memcmp(incomingCommandBuffer, "wifioff", 0x07)) return DISABLEWIFI_CMD;
    if(!memcmp(incomingCommandBuffer, "bton", 0x04)) return ENABLEBT_CMD;
    if(!memcmp(incomingCommandBuffer, "btoff", 0x05)) return DISABLEBT_CMD;
    if(!memcmp(incomingCommandBuffer, "demo1", 0x05)) return DEMO1_CMD;
    if(!memcmp(incomingCommandBuffer, "demo2", 0x05)) return DEMO2_CMD;
    if(!memcmp(incomingCommandBuffer, "stopdemo", 0x08)) return STOP_DEMO_CMD;
    if(!memcmp(incomingCommandBuffer, "reset", 0x05)) return RESET_CMD;
    if(!memcmp(incomingCommandBuffer, "readraw", 0x07)) return READ_RAW_CMD;

    return returnValue;
}



void handleCommand(GAME_COMMAND_T command)
{
    switch(command)
    {
        case STATUS_CMD:
            consolePrintStatus();
            break;

        case VERSION_CMD:
            consolePrintVersion();
            break;

        case HELP_CMD:
            consolePrintHelp();
            break;

        case GETLEVEL_CMD:
            consolePrintLevels();
            break;

        case GETSYSTICK_CMD:
            consolePrintSystick();
            break;

        case START_CMD:
            gameStateRequest = 	REQUEST_START;
            break;

        case PAUSE_CMD:
            gameStateRequest = 	REQUEST_PAUSE;
            break;

            case RESUME_CMD:
            gameStateRequest = REQUEST_RESUME;
            break;

        case ABORT_CMD:
            gameStateRequest = 	REQUEST_ABORT;
            break;

        case LEFT_PUMP_CMD:
        	if(leftPumpRequest != 255) leftPumpRequest++;

            break;

        case RIGHT_PUMP_CMD:
        	if(rightPumpRequest != 255) rightPumpRequest++;
            break;

        case ENABLEWIFI_CMD:
            break;

        case DISABLEWIFI_CMD:
            break;

        case ENABLEBT_CMD:
            break;

        case DISABLEBT_CMD:
            break;

        case DEMO1_CMD:
            gameStateRequest = REQUEST_DEMO_1;
            break;

        case DEMO2_CMD:
            gameStateRequest = REQUEST_DEMO_2;
            break;

        case STOP_DEMO_CMD:
            gameStateRequest = REQUEST_STOP_DEMO;
            break;

        case RESET_CMD:
            gameStateRequest = REQUEST_RESET;
            break;

        case READ_RAW_CMD:
            reportRawLevels();
            break;
        
        case RAWON_CMD:
            break;

        case RAWOFF_CMD:
            break;

        case ERROR_CMD:        
        default:

            break;
    }
}

// void kickConsoleTX(void)
// {
//     // consoleTXenabled = 1;
//     // Cy_SCB_UART_Put(consoleUART_HW, *txSendPtr);
//     // txSendPtr++;
// }




// void addToTXbuffer(char* string)
// {
//     uint8_t index;
//     while(txWriteLock);
//     for(index = 0; index < strlen(string); index++)
//     {
//         *txEndPtr = string[index];
//         txEndPtr++;
//         if(txEndPtr == (txBuffer + CONSOLE_TXBUFFER_SIZE)) txEndPtr = txBuffer;
//     }

//     if(!consoleTXenabled)
//     {
//         kickConsoleTX();
//     }
// }

