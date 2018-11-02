/*
 * command_console.h
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_

#include "cy_pdl.h"

typedef enum{
    DEMO1_CMD,
    DEMO2_CMD,
    STOP_DEMO_CMD,
    RESET_CMD,
    STATUS_CMD,
    VERSION_CMD,
    HELP_CMD,
    GETLEVEL_CMD,
    GETSYSTICK_CMD,
    START_CMD,
    PAUSE_CMD,
	RESUME_CMD,
    ABORT_CMD,
    LEFT_PUMP_CMD,
    RIGHT_PUMP_CMD,
    ENABLEWIFI_CMD,
    DISABLEWIFI_CMD,
    ENABLEBT_CMD,
    DISABLEBT_CMD,
    READ_RAW_CMD,
    RAWON_CMD,
    RAWOFF_CMD,
    ERROR_CMD    
}GAME_COMMAND_T;

typedef enum{
	NO_INCOMING_CMD,
	NEW_INCOMING_CMD
}INCOMING_CMD_T;

extern cy_stc_scb_uart_context_t consoleUARTcontext;
extern INCOMING_CMD_T incomingCommand;



//low level exposed functions
extern void initConsoleUART(void);
//extern void consoleUARTinterrupt(void);
//extern void addToTXbuffer(char* string);

//high level exposed functions
extern void consolePrintWelcome(void);
extern void consolePrintHelp(void);
extern void consolePrintSystick(void);
extern void consolePrintVersion(void);
extern void consolePrintPumpSpeed(void);
extern void consolePrintGameAbort(void);
extern void consolePrintGameState(void);
extern void consolePrintWin(void);

extern void handleIncomingCommand(void);

#endif /* SOURCE_COMMAND_CONSOLE_H_ */
