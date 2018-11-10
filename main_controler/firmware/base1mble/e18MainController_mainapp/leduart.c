/*
 * command_console.c
 *
 *  Created on: Sep 21, 2018
 *      Author: kmwh
 */

#include "cycfg.h"
#include "leduart.h"
#include "cy_pdl.h"
#include "platform_isr_interface.h"         //need for WICED interrupt definition

#define LED_TXBUFFER_SIZE   20

cy_stc_sysint_t ledUartIntrCfg =
     {
             .intrSrc = scb_1_interrupt_IRQn, /* Interrupt source is GPIO port 0 interrupt */
             .intrPriority = 5UL                     /* Interrupt priority is 2 */
     };

cy_stc_scb_uart_context_t ledUARTcontext;

uint8_t ledtxBuffer[LED_TXBUFFER_SIZE];
uint8_t* ledtxEndPtr = ledtxBuffer;
uint8_t* ledtxSendPtr = ledtxBuffer;
uint8_t ledTXenabled;
static uint8_t ledtxWriteLock = 0;
led_color_t leftColor;
led_color_t rightColor;

//local function declarations
void kickledTX(void);

// code
void ledUARTinit(void)
{
    //UART to LED driver
    Cy_SCB_UART_Init(ledUART_HW, &ledUART_config, &ledUARTcontext);
    Cy_SCB_UART_Enable(ledUART_HW);
 	Cy_SysInt_Init(&ledUartIntrCfg, &scb_1_interrupt_IRQn_Handler);
 	NVIC_EnableIRQ(ledUartIntrCfg.intrSrc);
}


void ledUARTsendColorValues(uint8_t leftValue, uint8_t rightValue)
{
    ledtxBuffer[0] = 'L';
    ledtxBuffer[1] = leftValue;    
    ledtxBuffer[2] = leftColor.red;
    ledtxBuffer[3] = leftColor.green;
    ledtxBuffer[4] = leftColor.blue;
    ledtxBuffer[5] = 'R';
    ledtxBuffer[6] = rightValue;
    ledtxBuffer[7] = rightColor.red;
    ledtxBuffer[8] = rightColor.green;
    ledtxBuffer[9] = rightColor.blue;
    ledtxBuffer[10] = 0x0D;
    ledtxSendPtr = ledtxBuffer;
    ledtxEndPtr = ledtxBuffer + 11;
    kickledTX();
    
}

//uart interrupt handler; checks for many events we're not using in this example
void scb_1_interrupt_IRQn_Handler(void)
{
    uint32_t cause = Cy_SCB_GetInterruptCause(ledUART_HW);
    uint32_t status;

    if(cause & CY_SCB_RX_INTR)
    {
        /* Get RX error events: a frame error, parity error, and overflow */
        status = Cy_SCB_GetRxInterruptStatusMasked(ledUART_HW);

        /* Handle the error conditions */
        if(status & CY_SCB_UART_RECEIVE_ERR)   //0UL != locRxErr)
        {
            Cy_SCB_ClearRxInterrupt(ledUART_HW, (status & CY_SCB_UART_RECEIVE_ERR));
        }

        /* Break detect */
        if(status & CY_SCB_RX_INTR_UART_BREAK_DETECT)
        {
            Cy_SCB_ClearRxInterrupt(ledUART_HW, CY_SCB_RX_INTR_UART_BREAK_DETECT);
        }

        /* Copy the received data */
        if(status & CY_SCB_RX_INTR_LEVEL)
        {
			Cy_SCB_ClearRxInterrupt(ledUART_HW, CY_SCB_RX_INTR_LEVEL);
        }

        if(status & CY_SCB_RX_INTR_NOT_EMPTY)
        {
			Cy_SCB_ClearRxInterrupt(ledUART_HW, CY_SCB_RX_INTR_NOT_EMPTY);
        }
    }

    if(cause & CY_SCB_TX_INTR)
    {
        status = Cy_SCB_GetTxInterruptStatusMasked(ledUART_HW);

        /* Handle the TX error conditions */
        if(status & CY_SCB_UART_TRANSMIT_ERR)
        {
            Cy_SCB_ClearTxInterrupt(ledUART_HW, (status & CY_SCB_UART_TRANSMIT_ERR));
        }

        /* Handle the TX complete */
        if(status & CY_SCB_TX_INTR_UART_DONE)
        {
            if(ledTXenabled)
            {
                ledtxWriteLock = 1;
                Cy_SCB_UART_Put(ledUART_HW, *ledtxSendPtr);
                ledtxSendPtr++;
                if(ledtxSendPtr == (ledtxBuffer + LED_TXBUFFER_SIZE)) ledtxSendPtr = ledtxBuffer;
                if(ledtxSendPtr == ledtxEndPtr)
                {
                    ledTXenabled = 0;                
                }
                ledtxWriteLock = 0;

                if(ledtxSendPtr < ledtxBuffer || ledtxSendPtr > (ledtxBuffer + LED_TXBUFFER_SIZE))
                {
                	//this is bad (shouldn't happen), attempt to recover by resetting the pointer
                	ledtxSendPtr = ledtxBuffer;
                }
            }
            Cy_SCB_ClearTxInterrupt(ledUART_HW, CY_SCB_TX_INTR_UART_DONE);
        }

        if(status & CY_SCB_TX_INTR_EMPTY)
        {
            Cy_SCB_ClearTxInterrupt(ledUART_HW, CY_SCB_TX_INTR_EMPTY);
        }
    }
}



void kickledTX(void)
{
    ledTXenabled = 1;
    Cy_SCB_UART_Put(ledUART_HW, *ledtxSendPtr);
    ledtxSendPtr++;
}

