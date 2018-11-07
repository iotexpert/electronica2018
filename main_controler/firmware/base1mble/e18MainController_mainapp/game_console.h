/*
 * command_console.h
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_

//low level exposed functions
extern void initGameConsole(void);

//high level exposed functions
extern void consolePrintWelcome(void);
extern void consolePrintWin(void);
extern void consolePrintHelp(void);         
extern void consolePrintStatus(void);

#endif /* SOURCE_COMMAND_CONSOLE_H_ */
