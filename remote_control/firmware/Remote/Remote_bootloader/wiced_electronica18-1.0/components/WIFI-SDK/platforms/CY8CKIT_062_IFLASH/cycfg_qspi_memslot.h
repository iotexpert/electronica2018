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
/*******************************************************************************
* \file cycfg_qspi_memslot.h
* \version 1.0
*
* \brief
* Provides declarations of the SMIF-driver memory configuration.
*
* Note: This is an auto generated file. Do not modify it.
*
********************************************************************************
* \copyright
* Copyright 2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/*******************************************************************************

QSPI_CONFIG_START

<CySMIFConfiguration>
    <DevicePath>PSoC 6.xml</DevicePath>
    <SlotConfigs>
        <SlotConfig>
            <SlaveSlot>0</SlaveSlot>
            <PartNumber>S25FL512S</PartNumber>
            <MemoryMapped>false</MemoryMapped>
            <DualQuad>None</DualQuad>
            <StartAddress>0x18000000</StartAddress>
            <Size>0x10000</Size>
            <EndAddress>0x1800FFFF</EndAddress>
            <WriteEnable>true</WriteEnable>
            <Encrypt>false</Encrypt>
            <DataSelect>QUAD_SPI_DATA_0_3</DataSelect>
            <MemoryConfigsPath>S25FL512S</MemoryConfigsPath>
            <ConfigDataInFlash>false</ConfigDataInFlash>
        </SlotConfig>
        <SlotConfig>
            <SlaveSlot>1</SlaveSlot>
            <PartNumber>Not used</PartNumber>
            <MemoryMapped>false</MemoryMapped>
            <DualQuad>None</DualQuad>
            <StartAddress>0x18010000</StartAddress>
            <Size>0x10000</Size>
            <EndAddress>0x1801FFFF</EndAddress>
            <WriteEnable>false</WriteEnable>
            <Encrypt>false</Encrypt>
            <DataSelect>SPI_MOSI_MISO_DATA_0_1</DataSelect>
            <MemoryConfigsPath>default_memory.xml</MemoryConfigsPath>
            <ConfigDataInFlash>false</ConfigDataInFlash>
        </SlotConfig>
        <SlotConfig>
            <SlaveSlot>2</SlaveSlot>
            <PartNumber>Not used</PartNumber>
            <MemoryMapped>false</MemoryMapped>
            <DualQuad>None</DualQuad>
            <StartAddress>0x18020000</StartAddress>
            <Size>0x10000</Size>
            <EndAddress>0x1802FFFF</EndAddress>
            <WriteEnable>false</WriteEnable>
            <Encrypt>false</Encrypt>
            <DataSelect>SPI_MOSI_MISO_DATA_0_1</DataSelect>
            <MemoryConfigsPath>default_memory.xml</MemoryConfigsPath>
            <ConfigDataInFlash>false</ConfigDataInFlash>
        </SlotConfig>
        <SlotConfig>
            <SlaveSlot>3</SlaveSlot>
            <PartNumber>Not used</PartNumber>
            <MemoryMapped>false</MemoryMapped>
            <DualQuad>None</DualQuad>
            <StartAddress>0x18030000</StartAddress>
            <Size>0x10000</Size>
            <EndAddress>0x1803FFFF</EndAddress>
            <WriteEnable>false</WriteEnable>
            <Encrypt>false</Encrypt>
            <DataSelect>SPI_MOSI_MISO_DATA_0_1</DataSelect>
            <MemoryConfigsPath>default_memory.xml</MemoryConfigsPath>
            <ConfigDataInFlash>false</ConfigDataInFlash>
        </SlotConfig>
    </SlotConfigs>
</CySMIFConfiguration>

QSPI_CONFIG_END

*******************************************************************************/

#ifndef CYCFG_QSPI_MEMSLOT_H
#define CYCFG_QSPI_MEMSLOT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "cy_smif_memslot.h"

#define CY_SMIF_DEVICE_NUM 1

extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_readCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_writeEnCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_writeDisCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_eraseCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_chipEraseCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_programCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_readStsRegQeCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_readStsRegWipCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_writeStsRegQeCmd;

extern cy_stc_smif_mem_device_cfg_t deviceCfg_S25FL512S_SlaveSlot_0;

extern const cy_stc_smif_mem_config_t S25FL512S_SlaveSlot_0;
extern const cy_stc_smif_mem_config_t* smifMemConfigs[CY_SMIF_DEVICE_NUM];

extern const cy_stc_smif_block_config_t smifBlockConfig;

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /*CY_SMIF_MEMCONFIG_H*/
