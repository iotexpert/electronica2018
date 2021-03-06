/*******************************************************************************
* File Name: cycfg_clocks.h
*
* Description:
* Clock configuration
* This file should not be modified. It was automatically generated by 
* ModusToolbox 1.0.0
* 
********************************************************************************
* Copyright (c) 2017-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CYCFG_CLOCKS_H)
#define CYCFG_CLOCKS_H

#include "cycfg_notices.h"
#include "cy_sysclk.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define peri_0_div_16_0_HW CY_SYSCLK_DIV_16_BIT
#define peri_0_div_16_0_NUM 0U
#define peri_0_div_16_1_HW CY_SYSCLK_DIV_16_BIT
#define peri_0_div_16_1_NUM 1U
#define peri_0_div_16_2_HW CY_SYSCLK_DIV_16_BIT
#define peri_0_div_16_2_NUM 2U
#define peri_0_div_8_0_HW CY_SYSCLK_DIV_8_BIT
#define peri_0_div_8_0_NUM 0U
#define peri_0_div_8_1_HW CY_SYSCLK_DIV_8_BIT
#define peri_0_div_8_1_NUM 1U
#define peri_0_div_8_2_HW CY_SYSCLK_DIV_8_BIT
#define peri_0_div_8_2_NUM 2U
#define peri_0_div_8_3_HW CY_SYSCLK_DIV_8_BIT
#define peri_0_div_8_3_NUM 3U
#define peri_0_div_8_6_HW CY_SYSCLK_DIV_8_BIT
#define peri_0_div_8_6_NUM 6U
#define peri_0_div_8_7_HW CY_SYSCLK_DIV_8_BIT
#define peri_0_div_8_7_NUM 7U

void init_cycfg_clocks(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_CLOCKS_H */
