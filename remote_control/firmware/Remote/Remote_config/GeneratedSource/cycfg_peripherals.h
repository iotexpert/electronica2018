/*******************************************************************************
* File Name: cycfg_peripherals.h
*
* Description:
* Peripheral Hardware Block configuration
* This file should not be modified. It was automatically generated by 
* ModusToolbox 1.0.0
* 
********************************************************************************
* Copyright (c) 2017-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CYCFG_PERIPHERALS_H)
#define CYCFG_PERIPHERALS_H

#include "cycfg_notices.h"
#include "cy_sysclk.h"
#include "cy_csd.h"
#include "cy_scb_uart.h"
#include "cy_smif.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define CY_CAPSENSE_CORE 4u
#define CY_CAPSENSE_CPU_CLK 100000000u
#define CY_CAPSENSE_PERI_CLK 100000000u
#define CY_CAPSENSE_VDDA_MV 3300u
#define CY_CAPSENSE_PERI_DIV_TYPE CY_SYSCLK_DIV_16_BIT
#define CY_CAPSENSE_PERI_DIV_INDEX 0u
#define Cmod_PORT GPIO_PRT7
#define BTBTN_Sns0_PORT GPIO_PRT8
#define WIFIBTN_Sns0_PORT GPIO_PRT8
#define Slider_Sns0_PORT GPIO_PRT8
#define Slider_Sns1_PORT GPIO_PRT8
#define Slider_Sns2_PORT GPIO_PRT8
#define Slider_Sns3_PORT GPIO_PRT8
#define Slider_Sns4_PORT GPIO_PRT8
#define Cmod_PIN 7u
#define BTBTN_Sns0_PIN 1u
#define WIFIBTN_Sns0_PIN 6u
#define Slider_Sns0_PIN 5u
#define Slider_Sns1_PIN 2u
#define Slider_Sns2_PIN 4u
#define Slider_Sns3_PIN 3u
#define Slider_Sns4_PIN 7u
#define Cmod_PORT_NUM 7u
#define CapSense_HW CSD0
#define CapSense_IRQ csd_interrupt_IRQn
#define scb_5_HW SCB5
#define scb_5_IRQ scb_5_interrupt_IRQn
#define smif_HW SMIF0
#define smif_IRQ smif_interrupt_IRQn
#define smif_MEMORY_MODE_ALIGMENT_ERROR (0UL)
#define smif_RX_DATA_FIFO_UNDERFLOW (0UL)
#define smif_TX_COMMAND_FIFO_OVERFLOW (0UL)
#define smif_TX_DATA_FIFO_OVERFLOW (0UL)
#define smif_RX_FIFO_TRIGEER_LEVEL (0UL)
#define smif_TX_FIFO_TRIGEER_LEVEL (0UL)
#define smif_DATALINES0_1 (1UL)
#define smif_DATALINES2_3 (1UL)
#define smif_DATALINES4_5 (0UL)
#define smif_DATALINES6_7 (0UL)
#define smif_SS0 (1UL)
#define smif_SS1 (0UL)
#define smif_SS2 (0UL)
#define smif_SS3 (0UL)
#define smif_DESELECT_DELAY 7

extern cy_stc_csd_context_t cy_csd_0_context;
extern const cy_stc_scb_uart_config_t scb_5_config;
extern const cy_stc_smif_config_t smif_config;

void init_cycfg_peripherals(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PERIPHERALS_H */
