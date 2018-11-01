/*******************************************************************************
* File Name: cycfg_pins.h
*
* Description:
* Pin configuration
* This file should not be modified. It was automatically generated by 
* ModusToolbox 1.0.0
* 
********************************************************************************
* Copyright (c) 2017-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_connectivity.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define ioss_0_port_11_pin_2_PORT GPIO_PRT11
#define ioss_0_port_11_pin_2_PIN 2U
#define ioss_0_port_11_pin_2_NUM 2U
#define ioss_0_port_11_pin_2_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_11_pin_2_INIT_DRIVESTATE 1
#ifndef ioss_0_port_11_pin_2_HSIOM
	#define ioss_0_port_11_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_11_pin_2_IRQ ioss_interrupts_gpio_11_IRQn
#define ioss_0_port_11_pin_3_PORT GPIO_PRT11
#define ioss_0_port_11_pin_3_PIN 3U
#define ioss_0_port_11_pin_3_NUM 3U
#define ioss_0_port_11_pin_3_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_11_pin_3_INIT_DRIVESTATE 1
#ifndef ioss_0_port_11_pin_3_HSIOM
	#define ioss_0_port_11_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_11_pin_3_IRQ ioss_interrupts_gpio_11_IRQn
#define ioss_0_port_11_pin_4_PORT GPIO_PRT11
#define ioss_0_port_11_pin_4_PIN 4U
#define ioss_0_port_11_pin_4_NUM 4U
#define ioss_0_port_11_pin_4_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_11_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_11_pin_4_HSIOM
	#define ioss_0_port_11_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_11_pin_4_IRQ ioss_interrupts_gpio_11_IRQn
#define ioss_0_port_11_pin_5_PORT GPIO_PRT11
#define ioss_0_port_11_pin_5_PIN 5U
#define ioss_0_port_11_pin_5_NUM 5U
#define ioss_0_port_11_pin_5_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_11_pin_5_INIT_DRIVESTATE 1
#ifndef ioss_0_port_11_pin_5_HSIOM
	#define ioss_0_port_11_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_11_pin_5_IRQ ioss_interrupts_gpio_11_IRQn
#define ioss_0_port_11_pin_6_PORT GPIO_PRT11
#define ioss_0_port_11_pin_6_PIN 6U
#define ioss_0_port_11_pin_6_NUM 6U
#define ioss_0_port_11_pin_6_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_11_pin_6_INIT_DRIVESTATE 1
#ifndef ioss_0_port_11_pin_6_HSIOM
	#define ioss_0_port_11_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_11_pin_6_IRQ ioss_interrupts_gpio_11_IRQn
#define ioss_0_port_11_pin_7_PORT GPIO_PRT11
#define ioss_0_port_11_pin_7_PIN 7U
#define ioss_0_port_11_pin_7_NUM 7U
#define ioss_0_port_11_pin_7_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_11_pin_7_INIT_DRIVESTATE 1
#ifndef ioss_0_port_11_pin_7_HSIOM
	#define ioss_0_port_11_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_11_pin_7_IRQ ioss_interrupts_gpio_11_IRQn
#define ioss_0_port_2_pin_0_PORT GPIO_PRT2
#define ioss_0_port_2_pin_0_PIN 0U
#define ioss_0_port_2_pin_0_NUM 0U
#define ioss_0_port_2_pin_0_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_2_pin_0_INIT_DRIVESTATE 1
#ifndef ioss_0_port_2_pin_0_HSIOM
	#define ioss_0_port_2_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_2_pin_0_IRQ ioss_interrupts_gpio_2_IRQn
#define ioss_0_port_2_pin_1_PORT GPIO_PRT2
#define ioss_0_port_2_pin_1_PIN 1U
#define ioss_0_port_2_pin_1_NUM 1U
#define ioss_0_port_2_pin_1_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_2_pin_1_INIT_DRIVESTATE 1
#ifndef ioss_0_port_2_pin_1_HSIOM
	#define ioss_0_port_2_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_2_pin_1_IRQ ioss_interrupts_gpio_2_IRQn
#define ioss_0_port_2_pin_2_PORT GPIO_PRT2
#define ioss_0_port_2_pin_2_PIN 2U
#define ioss_0_port_2_pin_2_NUM 2U
#define ioss_0_port_2_pin_2_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_2_pin_2_INIT_DRIVESTATE 1
#ifndef ioss_0_port_2_pin_2_HSIOM
	#define ioss_0_port_2_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_2_pin_2_IRQ ioss_interrupts_gpio_2_IRQn
#define ioss_0_port_2_pin_3_PORT GPIO_PRT2
#define ioss_0_port_2_pin_3_PIN 3U
#define ioss_0_port_2_pin_3_NUM 3U
#define ioss_0_port_2_pin_3_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_2_pin_3_INIT_DRIVESTATE 1
#ifndef ioss_0_port_2_pin_3_HSIOM
	#define ioss_0_port_2_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_2_pin_3_IRQ ioss_interrupts_gpio_2_IRQn
#define ioss_0_port_2_pin_4_PORT GPIO_PRT2
#define ioss_0_port_2_pin_4_PIN 4U
#define ioss_0_port_2_pin_4_NUM 4U
#define ioss_0_port_2_pin_4_DRIVEMODE CY_GPIO_DM_STRONG
#define ioss_0_port_2_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_2_pin_4_HSIOM
	#define ioss_0_port_2_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_2_pin_4_IRQ ioss_interrupts_gpio_2_IRQn
#define ioss_0_port_2_pin_5_PORT GPIO_PRT2
#define ioss_0_port_2_pin_5_PIN 5U
#define ioss_0_port_2_pin_5_NUM 5U
#define ioss_0_port_2_pin_5_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_2_pin_5_INIT_DRIVESTATE 1
#ifndef ioss_0_port_2_pin_5_HSIOM
	#define ioss_0_port_2_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_2_pin_5_IRQ ioss_interrupts_gpio_2_IRQn
#define ioss_0_port_2_pin_6_PORT GPIO_PRT2
#define ioss_0_port_2_pin_6_PIN 6U
#define ioss_0_port_2_pin_6_NUM 6U
#define ioss_0_port_2_pin_6_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_2_pin_6_INIT_DRIVESTATE 0
#ifndef ioss_0_port_2_pin_6_HSIOM
	#define ioss_0_port_2_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_2_pin_6_IRQ ioss_interrupts_gpio_2_IRQn
#define ioss_0_port_5_pin_0_PORT GPIO_PRT5
#define ioss_0_port_5_pin_0_PIN 0U
#define ioss_0_port_5_pin_0_NUM 0U
#define ioss_0_port_5_pin_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define ioss_0_port_5_pin_0_INIT_DRIVESTATE 1
#ifndef ioss_0_port_5_pin_0_HSIOM
	#define ioss_0_port_5_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_5_pin_0_IRQ ioss_interrupts_gpio_5_IRQn
#define ioss_0_port_5_pin_1_PORT GPIO_PRT5
#define ioss_0_port_5_pin_1_PIN 1U
#define ioss_0_port_5_pin_1_NUM 1U
#define ioss_0_port_5_pin_1_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_5_pin_1_INIT_DRIVESTATE 1
#ifndef ioss_0_port_5_pin_1_HSIOM
	#define ioss_0_port_5_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_5_pin_1_IRQ ioss_interrupts_gpio_5_IRQn
#define ioss_0_port_6_pin_4_PORT GPIO_PRT6
#define ioss_0_port_6_pin_4_PIN 4U
#define ioss_0_port_6_pin_4_NUM 4U
#define ioss_0_port_6_pin_4_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_6_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_4_HSIOM
	#define ioss_0_port_6_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_4_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_6_PORT GPIO_PRT6
#define ioss_0_port_6_pin_6_PIN 6U
#define ioss_0_port_6_pin_6_NUM 6U
#define ioss_0_port_6_pin_6_DRIVEMODE CY_GPIO_DM_PULLUP
#define ioss_0_port_6_pin_6_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_6_HSIOM
	#define ioss_0_port_6_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_6_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_7_PORT GPIO_PRT6
#define ioss_0_port_6_pin_7_PIN 7U
#define ioss_0_port_6_pin_7_NUM 7U
#define ioss_0_port_6_pin_7_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define ioss_0_port_6_pin_7_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_7_HSIOM
	#define ioss_0_port_6_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_7_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_7_pin_7_PORT GPIO_PRT7
#define ioss_0_port_7_pin_7_PIN 7U
#define ioss_0_port_7_pin_7_NUM 7U
#define ioss_0_port_7_pin_7_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_7_pin_7_INIT_DRIVESTATE 1
#ifndef ioss_0_port_7_pin_7_HSIOM
	#define ioss_0_port_7_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_7_pin_7_IRQ ioss_interrupts_gpio_7_IRQn
#define ioss_0_port_8_pin_1_PORT GPIO_PRT8
#define ioss_0_port_8_pin_1_PIN 1U
#define ioss_0_port_8_pin_1_NUM 1U
#define ioss_0_port_8_pin_1_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_8_pin_1_INIT_DRIVESTATE 1
#ifndef ioss_0_port_8_pin_1_HSIOM
	#define ioss_0_port_8_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_8_pin_1_IRQ ioss_interrupts_gpio_8_IRQn
#define ioss_0_port_8_pin_2_PORT GPIO_PRT8
#define ioss_0_port_8_pin_2_PIN 2U
#define ioss_0_port_8_pin_2_NUM 2U
#define ioss_0_port_8_pin_2_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_8_pin_2_INIT_DRIVESTATE 1
#ifndef ioss_0_port_8_pin_2_HSIOM
	#define ioss_0_port_8_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_8_pin_2_IRQ ioss_interrupts_gpio_8_IRQn
#define ioss_0_port_8_pin_3_PORT GPIO_PRT8
#define ioss_0_port_8_pin_3_PIN 3U
#define ioss_0_port_8_pin_3_NUM 3U
#define ioss_0_port_8_pin_3_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_8_pin_3_INIT_DRIVESTATE 1
#ifndef ioss_0_port_8_pin_3_HSIOM
	#define ioss_0_port_8_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_8_pin_3_IRQ ioss_interrupts_gpio_8_IRQn
#define ioss_0_port_8_pin_4_PORT GPIO_PRT8
#define ioss_0_port_8_pin_4_PIN 4U
#define ioss_0_port_8_pin_4_NUM 4U
#define ioss_0_port_8_pin_4_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_8_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_8_pin_4_HSIOM
	#define ioss_0_port_8_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_8_pin_4_IRQ ioss_interrupts_gpio_8_IRQn
#define ioss_0_port_8_pin_5_PORT GPIO_PRT8
#define ioss_0_port_8_pin_5_PIN 5U
#define ioss_0_port_8_pin_5_NUM 5U
#define ioss_0_port_8_pin_5_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_8_pin_5_INIT_DRIVESTATE 1
#ifndef ioss_0_port_8_pin_5_HSIOM
	#define ioss_0_port_8_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_8_pin_5_IRQ ioss_interrupts_gpio_8_IRQn
#define ioss_0_port_8_pin_6_PORT GPIO_PRT8
#define ioss_0_port_8_pin_6_PIN 6U
#define ioss_0_port_8_pin_6_NUM 6U
#define ioss_0_port_8_pin_6_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_8_pin_6_INIT_DRIVESTATE 1
#ifndef ioss_0_port_8_pin_6_HSIOM
	#define ioss_0_port_8_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_8_pin_6_IRQ ioss_interrupts_gpio_8_IRQn
#define ioss_0_port_8_pin_7_PORT GPIO_PRT8
#define ioss_0_port_8_pin_7_PIN 7U
#define ioss_0_port_8_pin_7_NUM 7U
#define ioss_0_port_8_pin_7_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_8_pin_7_INIT_DRIVESTATE 1
#ifndef ioss_0_port_8_pin_7_HSIOM
	#define ioss_0_port_8_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_8_pin_7_IRQ ioss_interrupts_gpio_8_IRQn
#define BT_LED_PORT GPIO_PRT9
#define BT_LED_PIN 3U
#define BT_LED_NUM 3U
#define BT_LED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define BT_LED_INIT_DRIVESTATE 1
#ifndef ioss_0_port_9_pin_3_HSIOM
	#define ioss_0_port_9_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define BT_LED_HSIOM ioss_0_port_9_pin_3_HSIOM
#define BT_LED_IRQ ioss_interrupts_gpio_9_IRQn
#define WIFI_LED_PORT GPIO_PRT9
#define WIFI_LED_PIN 5U
#define WIFI_LED_NUM 5U
#define WIFI_LED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define WIFI_LED_INIT_DRIVESTATE 1
#ifndef ioss_0_port_9_pin_5_HSIOM
	#define ioss_0_port_9_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define WIFI_LED_HSIOM ioss_0_port_9_pin_5_HSIOM
#define WIFI_LED_IRQ ioss_interrupts_gpio_9_IRQn
#define SLD_LED_PORT GPIO_PRT9
#define SLD_LED_PIN 7U
#define SLD_LED_NUM 7U
#define SLD_LED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define SLD_LED_INIT_DRIVESTATE 1
#ifndef ioss_0_port_9_pin_7_HSIOM
	#define ioss_0_port_9_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define SLD_LED_HSIOM ioss_0_port_9_pin_7_HSIOM
#define SLD_LED_IRQ ioss_interrupts_gpio_9_IRQn

extern const cy_stc_gpio_pin_config_t ioss_0_port_11_pin_2_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_11_pin_3_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_11_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_11_pin_5_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_11_pin_6_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_11_pin_7_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_2_pin_0_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_2_pin_1_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_2_pin_2_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_2_pin_3_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_2_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_2_pin_5_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_2_pin_6_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_5_pin_0_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_5_pin_1_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_6_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_7_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_7_pin_7_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_8_pin_1_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_8_pin_2_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_8_pin_3_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_8_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_8_pin_5_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_8_pin_6_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_8_pin_7_config;
extern const cy_stc_gpio_pin_config_t BT_LED_config;
extern const cy_stc_gpio_pin_config_t WIFI_LED_config;
extern const cy_stc_gpio_pin_config_t SLD_LED_config;

void init_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PINS_H */
