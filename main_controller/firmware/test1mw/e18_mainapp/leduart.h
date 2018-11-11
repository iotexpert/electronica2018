/*
 * command_console.h
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */


#ifndef LED_UART_H
#define LED_UART_H

#include "cy_pdl.h"


typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}LED_COLOR_T;

extern LED_COLOR_T leftColor;
extern LED_COLOR_T rightColor;

extern cy_stc_scb_uart_context_t ledUARTcontext;

extern void ledUARTinit(void);
extern void ledUARTsendSimpleValues(uint8_t leftValue, uint8_t rightValue);
extern void ledUARTsendColorValues(uint8_t leftValue, uint8_t rightValue);

#endif

