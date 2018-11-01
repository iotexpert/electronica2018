/* ========================================
 *
 * EX2_String
 *
 * A simple function to cycle the color table
 * through the string.
 *
 * ========================================
*/
#include "project.h"

typedef enum{
    RX_WAITING,
    RX_CMD_RCVD
}RX_STATUS_T;

typedef struct{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
    uint8_t none;
}COLOR_STRUCT_T;

typedef union{
    COLOR_STRUCT_T bytes;
    uint32_t word;
}COLOR_T;

//#define SLOW_BLEND_TEST


#define RX_BUFFER_SIZE  64

#define NUM_LEDS_STRIP 144
#define NUM_LEDS_100PERCENT 100

RX_STATUS_T rxStatus = RX_WAITING;
uint8_t incomingbytes[RX_BUFFER_SIZE];
uint8_t incomingCmd[RX_BUFFER_SIZE];

//extern uint32  StripLights_ledArray[StripLights_ROWS][StripLights_COLUMNS];


void SlowColorBlend(uint32 delay, uint32 time);
CY_ISR_PROTO(RX_interrupt);
void readLEDcommand(void);


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    StripLights_Start();
    
       
    isr_UART_RX_StartEx(RX_interrupt);
    UART_DEB_Start();       //debug serial start for development mode


    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

//    incomingCmd[0] = 'L';
//    incomingCmd[1] = 0x30;
//    incomingCmd[2] = 0x00;
//    incomingCmd[3] = 0x00;
//    incomingCmd[4] = 0xFF;
//    incomingCmd[5] = 'R';
//    incomingCmd[6] = 0x00;
//    
//    readLEDcommand();
    
    
   #ifdef SLOW_BLEND_TEST
        SlowColorBlend(5, 5);
   #endif
    
    
    while(1)
    {
        if(rxStatus == RX_CMD_RCVD)
        {
            readLEDcommand();
        }
        //SlowColorBlend(0, 10000);
       while( StripLights_Ready() == 0);
       StripLights_Trigger(1);
       CyDelay(100);
    }
}


void readLEDcommand(void)
{
    COLOR_T leftColor;
    COLOR_T rightColor;
    uint8_t index;
    uint8_t level;
    
    rxStatus = RX_WAITING;
    if(incomingCmd[0] == 'L' && incomingCmd[5] == 'R')
    {
        leftColor.bytes.none = 0x00;
        leftColor.bytes.red = incomingCmd[2];
        leftColor.bytes.green = incomingCmd[3];
        leftColor.bytes.blue = incomingCmd[4];
        
        level = (incomingCmd[1] * NUM_LEDS_STRIP)/100;
        
        for(index = 0; index < NUM_LEDS_STRIP; index++)
        {
            //StripLights_ledArray[0][index] = leftColor;
            if(index < level)
            {
                StripLights_Pixel(index, 0, leftColor.word);
            }
            else
            {
                StripLights_Pixel(index, 0, 0x00000000);
            }
        }

        rightColor.bytes.none = 0x00;
        rightColor.bytes.red = incomingCmd[7];
        rightColor.bytes.green = incomingCmd[8];
        rightColor.bytes.blue = incomingCmd[9];
                
        level = (incomingCmd[6] * NUM_LEDS_STRIP)/100;
        for(index = 0; index < NUM_LEDS_STRIP; index++)
        {
            //StripLights_ledArray[0][index] = leftColor;
            if(index < level)
            {
                StripLights_Pixel(index, 1, rightColor.word);
            }
            else
            {
                StripLights_Pixel(index, 1, 0x00000000);
            }
        }
                        
        StripLights_Trigger(1);        
    }
}




//debug serial port receive interrupt
CY_ISR(RX_interrupt)
{    
    static uint8 RXincomingptr = 0;
    uint8 RXbyte;
    uint32 mask;
    uint32 cause = UART_DEB_GetRxInterruptSourceMasked();
    //cause = UART_DEB_GetInterruptCause();
    
    mask = UART_DEB_INTR_RX_OVERFLOW;
    if(cause & mask)
    {
        UART_DEB_ClearRxInterruptSource(UART_DEB_INTR_RX_OVERFLOW);
        //UARTrxoverflow = UART_RX_FIFO_OVERFLOW;
    }
    
    mask = UART_DEB_INTR_RX_NOT_EMPTY;
    if(cause & mask)    
    {
        RXbyte = UART_DEB_UartGetByte();
        incomingbytes[RXincomingptr] = RXbyte;
        if(RXbyte == 0x0D)
        {
            rxStatus = RX_CMD_RCVD;
            memcpy(incomingCmd, incomingbytes, RXincomingptr);
            RXincomingptr = 0;
        }
        else
        {
            RXincomingptr++;
            if(RXincomingptr == RX_BUFFER_SIZE) RXincomingptr = 0;
        }
        UART_DEB_ClearRxInterruptSource(UART_DEB_INTR_RX_NOT_EMPTY);
    }
    
    //UART_DEB_ClearRxInterruptSource(UART_DEB_GetRxInterruptSource());
}





/************************************************
 *                    SlowColorBlend()
 *
 *  Slowly migate all the LEDs through the color
 *  table.
 *
 ************************************************/
void SlowColorBlend(uint32 delay, uint32 time)
{
    uint32 timeCnt = 0; 
    uint32 led = 0;
    uint32 x = 0;
    uint32 pct = 0;
    uint32 fromColor, toColor, color;
    extern const uint32 StripLights_CLUT[ ];

    StripLights_Dim(0); 

    for(;;)
    {   
        while(1)
        {
           
            for(pct = 0; pct < 100; pct += 4)
            {
                for(led = 0; led <= StripLights_MAX_X; led++)
                {
 
                    fromColor =  StripLights_CLUT[(x + 0 + ((led * StripLights_COLOR_WHEEL_SIZE)/StripLights_TOTAL_LEDS)) % StripLights_COLOR_WHEEL_SIZE];
                    toColor =  StripLights_CLUT[(x + 1 + ((led * StripLights_COLOR_WHEEL_SIZE)/StripLights_TOTAL_LEDS)) % StripLights_COLOR_WHEEL_SIZE];
                    
                    color = StripLights_RgbBlend(fromColor, toColor, pct);                  
                    StripLights_Pixel(led, 0, color );
                }
                
                 while( StripLights_Ready() == 0);
	
	            StripLights_Trigger(1);
                CyDelay(delay);

            }
            x++;  // Advance through color wheel
        }
        timeCnt += delay;
 
     
     if(SW1_Read() == 0) break;  // If SW1 pressed leave
         if(timeCnt > time) break;
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);  
}

/* [] END OF FILE */
