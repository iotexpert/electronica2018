/*
 * Copyright 2018, Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All Rights Reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software"), is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
*/

/***************************************************************************//**
* \file cycfg_init.c
* \version 1.0
*
* \brief
* Performs a basic PSoC 6 device initialization.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <stdbool.h>
#include "cy_syslib.h"
#include "cy_syspm.h"
#include "cycfg_platform.h"
#include "cycfg_clocks.h"
#include "cycfg_pins.h"
#include "cycfg_connectivity.h"
#include "cycfg_peripherals.h"
#include "cycfg_peripherals.h"
#include "SDIO_HOST_cfg.h"


/*******************************************************************************
* Function Name: Cy_SystemInit
****************************************************************************//**
*
* \brief This function is called by the start-up code for the selected device.
* It performs all of the necessary device configuration based on the design
* settings. This includes settings for the platform resources and peripheral
* clock.
*
*******************************************************************************/
void Cy_SystemInit(void)
{
    /* Configure platform resources */
    init_cycfg_platform();

    /* Configure peripheral clocks */
    init_cycfg_clocks();

    /* Enables connections */
    init_cycfg_connectivity();

    /* Initialize peripherals */
    init_cycfg_peripherals();

#if defined(UDB_SDIO)
    /* Initialize the UDBs */
    SDIO_Host_Config_UDBs();
#endif

    /* Initialize the pins */
    init_cycfg_pins();
}


/* [] END OF FILE */
