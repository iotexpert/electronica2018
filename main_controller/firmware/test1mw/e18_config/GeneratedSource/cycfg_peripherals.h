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
#include "cy_tcpwm_pwm.h"
#include "cycfg_connectivity.h"
#include "cy_tcpwm_counter.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define CY_CAPSENSE_CORE 4u
#define CY_CAPSENSE_CPU_CLK 100000000u
#define CY_CAPSENSE_PERI_CLK 100000000u
#define CY_CAPSENSE_VDDA_MV 3300u
#define CY_CAPSENSE_PERI_DIV_TYPE CY_SYSCLK_DIV_8_BIT
#define CY_CAPSENSE_PERI_DIV_INDEX 2u
#define CintA_PORT GPIO_PRT7
#define CintB_PORT GPIO_PRT7
#define leftSense0_Rx0_PORT GPIO_PRT9
#define leftSense0_Tx_PORT GPIO_PRT9
#define leftSense1_Rx0_PORT GPIO_PRT8
#define leftSense2_Rx0_PORT GPIO_PRT8
#define leftSense3_Rx0_PORT GPIO_PRT5
#define leftSense4_Rx0_PORT GPIO_PRT8
#define leftSense5_Rx0_PORT GPIO_PRT13
#define leftSense6_Rx0_PORT GPIO_PRT8
#define leftSense7_Rx0_PORT GPIO_PRT9
#define leftSense8_Rx0_PORT GPIO_PRT9
#define leftSense9_Rx0_PORT GPIO_PRT9
#define leftSense10_Rx0_PORT GPIO_PRT7
#define leftSense11_Rx0_PORT GPIO_PRT7
#define rightSense0_Rx0_PORT GPIO_PRT8
#define rightSense0_Tx_PORT GPIO_PRT1
#define rightSense1_Rx0_PORT GPIO_PRT5
#define rightSense2_Rx0_PORT GPIO_PRT9
#define rightSense3_Rx0_PORT GPIO_PRT8
#define rightSense4_Rx0_PORT GPIO_PRT8
#define rightSense5_Rx0_PORT GPIO_PRT8
#define rightSense6_Rx0_PORT GPIO_PRT5
#define rightSense7_Rx0_PORT GPIO_PRT0
#define rightSense8_Rx0_PORT GPIO_PRT13
#define rightSense9_Rx0_PORT GPIO_PRT1
#define rightSense10_Rx0_PORT GPIO_PRT1
#define rightSense11_Rx0_PORT GPIO_PRT1
#define CintA_PIN 1u
#define CintB_PIN 2u
#define leftSense0_Rx0_PIN 4u
#define leftSense0_Tx_PIN 0u
#define leftSense1_Rx0_PIN 0u
#define leftSense2_Rx0_PIN 2u
#define leftSense3_Rx0_PIN 4u
#define leftSense4_Rx0_PIN 3u
#define leftSense5_Rx0_PIN 1u
#define leftSense6_Rx0_PIN 1u
#define leftSense7_Rx0_PIN 5u
#define leftSense8_Rx0_PIN 1u
#define leftSense9_Rx0_PIN 2u
#define leftSense10_Rx0_PIN 6u
#define leftSense11_Rx0_PIN 3u
#define rightSense0_Rx0_PIN 7u
#define rightSense0_Tx_PIN 2u
#define rightSense1_Rx0_PIN 6u
#define rightSense2_Rx0_PIN 3u
#define rightSense3_Rx0_PIN 4u
#define rightSense4_Rx0_PIN 6u
#define rightSense5_Rx0_PIN 5u
#define rightSense6_Rx0_PIN 5u
#define rightSense7_Rx0_PIN 2u
#define rightSense8_Rx0_PIN 0u
#define rightSense9_Rx0_PIN 5u
#define rightSense10_Rx0_PIN 4u
#define rightSense11_Rx0_PIN 3u
#define CintA_PORT_NUM 7u
#define CintB_PORT_NUM 7u
#define csd_0_csd_0_HW CSD0
#define csd_0_csd_0_IRQ csd_interrupt_IRQn
#define ledUART_HW SCB1
#define ledUART_IRQ scb_1_interrupt_IRQn
#define scb_5_HW SCB5
#define scb_5_IRQ scb_5_interrupt_IRQn
#define rightPump_HW TCPWM0
#define rightPump_NUM 1UL
#define rightPump_MASK (1UL << 1)
#define leftPump_HW TCPWM0
#define leftPump_NUM 3UL
#define leftPump_MASK (1UL << 3)
#define audioSampleInt_HW TCPWM1
#define audioSampleInt_NUM 0UL
#define audioSampleInt_MASK (1UL << 0)
#define audioSampleInt_IRQ tcpwm_1_interrupts_0_IRQn
#define audioPWM_HW TCPWM1
#define audioPWM_NUM 2UL
#define audioPWM_MASK (1UL << 2)

extern cy_stc_csd_context_t cy_csd_0_context;
extern const cy_stc_scb_uart_config_t ledUART_config;
extern const cy_stc_scb_uart_config_t scb_5_config;
extern const cy_stc_tcpwm_pwm_config_t rightPump_config;
extern const cy_stc_tcpwm_pwm_config_t leftPump_config;
extern const cy_stc_tcpwm_counter_config_t audioSampleInt_config;
extern const cy_stc_tcpwm_pwm_config_t audioPWM_config;

void init_cycfg_peripherals(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PERIPHERALS_H */
