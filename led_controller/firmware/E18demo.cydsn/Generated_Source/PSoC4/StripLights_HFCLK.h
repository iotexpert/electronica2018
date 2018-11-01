/*******************************************************************************
* File Name: StripLights_HFCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_StripLights_HFCLK_H)
#define CY_CLOCK_StripLights_HFCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void StripLights_HFCLK_StartEx(uint32 alignClkDiv);
#define StripLights_HFCLK_Start() \
    StripLights_HFCLK_StartEx(StripLights_HFCLK__PA_DIV_ID)

#else

void StripLights_HFCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void StripLights_HFCLK_Stop(void);

void StripLights_HFCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 StripLights_HFCLK_GetDividerRegister(void);
uint8  StripLights_HFCLK_GetFractionalDividerRegister(void);

#define StripLights_HFCLK_Enable()                         StripLights_HFCLK_Start()
#define StripLights_HFCLK_Disable()                        StripLights_HFCLK_Stop()
#define StripLights_HFCLK_SetDividerRegister(clkDivider, reset)  \
    StripLights_HFCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define StripLights_HFCLK_SetDivider(clkDivider)           StripLights_HFCLK_SetDividerRegister((clkDivider), 1u)
#define StripLights_HFCLK_SetDividerValue(clkDivider)      StripLights_HFCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define StripLights_HFCLK_DIV_ID     StripLights_HFCLK__DIV_ID

#define StripLights_HFCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define StripLights_HFCLK_CTRL_REG   (*(reg32 *)StripLights_HFCLK__CTRL_REGISTER)
#define StripLights_HFCLK_DIV_REG    (*(reg32 *)StripLights_HFCLK__DIV_REGISTER)

#define StripLights_HFCLK_CMD_DIV_SHIFT          (0u)
#define StripLights_HFCLK_CMD_PA_DIV_SHIFT       (8u)
#define StripLights_HFCLK_CMD_DISABLE_SHIFT      (30u)
#define StripLights_HFCLK_CMD_ENABLE_SHIFT       (31u)

#define StripLights_HFCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << StripLights_HFCLK_CMD_DISABLE_SHIFT))
#define StripLights_HFCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << StripLights_HFCLK_CMD_ENABLE_SHIFT))

#define StripLights_HFCLK_DIV_FRAC_MASK  (0x000000F8u)
#define StripLights_HFCLK_DIV_FRAC_SHIFT (3u)
#define StripLights_HFCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define StripLights_HFCLK_DIV_INT_SHIFT  (8u)

#else 

#define StripLights_HFCLK_DIV_REG        (*(reg32 *)StripLights_HFCLK__REGISTER)
#define StripLights_HFCLK_ENABLE_REG     StripLights_HFCLK_DIV_REG
#define StripLights_HFCLK_DIV_FRAC_MASK  StripLights_HFCLK__FRAC_MASK
#define StripLights_HFCLK_DIV_FRAC_SHIFT (16u)
#define StripLights_HFCLK_DIV_INT_MASK   StripLights_HFCLK__DIVIDER_MASK
#define StripLights_HFCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_StripLights_HFCLK_H) */

/* [] END OF FILE */
