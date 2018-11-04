/*******************************************************************************
* File Name: cycfg_peripherals.c
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

#include "cycfg_peripherals.h"

const cy_stc_scb_uart_config_t scb_5_config = 
{
	.uartMode = CY_SCB_UART_STANDARD,
	.enableMutliProcessorMode = false,
	.smartCardRetryOnNack = false,
	.irdaInvertRx = false,
	.irdaEnableLowPowerReceiver = false,
	.oversample = 8,
	.enableMsbFirst = false,
	.dataWidth = 8UL,
	.parity = CY_SCB_UART_PARITY_NONE,
	.stopBits = CY_SCB_UART_STOP_BITS_1,
	.enableInputFilter = false,
	.breakWidth = 11UL,
	.dropOnFrameError = false,
	.dropOnParityError = false,
	.receiverAddress = 0x0UL,
	.receiverAddressMask = 0x0UL,
	.acceptAddrInFifo = false,
	.enableCts = false,
	.ctsPolarity = CY_SCB_UART_ACTIVE_LOW,
	.rtsRxFifoLevel = 0UL,
	.rtsPolarity = CY_SCB_UART_ACTIVE_LOW,
	.rxFifoTriggerLevel = 63UL,
	.rxFifoIntEnableMask = 0UL,
	.txFifoTriggerLevel = 63UL,
	.txFifoIntEnableMask = 0UL,
};
cy_en_sd_host_card_capacity_t sdhc_0_cardCapacity = CY_SD_HOST_SDSC;
cy_en_sd_host_card_type_t sdhc_0_cardType = CY_SD_HOST_NOT_EMMC;
uint32_t sdhc_0_rca = 0u;
const cy_stc_sd_host_init_config_t sdhc_0_config = 
{
	.emmc = false,
	.dmaType = CY_SD_HOST_DMA_SDMA,
	.enableLedControl = false,
};
cy_stc_sd_host_sd_card_config_t sdhc_0_card_cfg = 
{
	.lowVoltageSignaling = false,
	.busWidth = CY_SD_HOST_BUS_WIDTH_4_BIT,
	.cardType = &sdhc_0_cardType,
	.rca = &sdhc_0_rca,
	.cardCapacity = &sdhc_0_cardCapacity,
};
const cy_stc_smif_config_t smif_config = 
{
	.mode = (uint32_t)CY_SMIF_NORMAL,
	.deselectDelay = smif_DESELECT_DELAY,
	.rxClockSel = (uint32_t)CY_SMIF_SEL_INV_INTERNAL_CLK,
	.blockEvent = (uint32_t)CY_SMIF_BUS_ERROR,
};


void init_cycfg_peripherals(void)
{
	Cy_SysClk_PeriphAssignDivider(PCLK_SCB5_CLOCK, CY_SYSCLK_DIV_8_BIT, 1U);
}
