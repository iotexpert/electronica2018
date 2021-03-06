/*******************************************************************************
* File Name: cycfg_dmas.c
*
* Description:
* DMA configuration
* This file should not be modified. It was automatically generated by 
* ModusToolbox 1.0.0
* 
********************************************************************************
* Copyright (c) 2017-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cycfg_dmas.h"

cy_stc_dma_descriptor_config_t TxDMA_Descriptor_0_config = 
{
	.retrigger = CY_DMA_RETRIG_IM,
	.interruptType = CY_DMA_DESCR,
	.triggerOutType = CY_DMA_DESCR,
	.channelState = CY_DMA_CHANNEL_ENABLED,
	.triggerInType = CY_DMA_1ELEMENT,
	.dataSize = CY_DMA_BYTE,
	.srcTransferSize = CY_DMA_TRANSFER_SIZE_DATA,
	.dstTransferSize = CY_DMA_TRANSFER_SIZE_WORD,
	.descriptorType = CY_DMA_2D_TRANSFER,
	.srcAddress = NULL,
	.dstAddress = NULL,
	.srcXincrement = 1,
	.dstXincrement = 0,
	.xCount = 256,
	.srcYincrement = 256,
	.dstYincrement = 0,
	.yCount = 256,
	.nextDescriptor = &TxDMA_Descriptor_0,
};
cy_stc_dma_descriptor_t TxDMA_Descriptor_0 = 
{
	.ctl = 0UL,
	.src = 0UL,
	.dst = 0UL,
	.xCtl = 0UL,
	.yCtl = 0UL,
	.nextPtr = 0UL,
};
cy_stc_dma_channel_config_t TxDMA_channelConfig = 
{
	.descriptor = &TxDMA_Descriptor_0,
	.preemptable = false,
	.priority = 3,
	.enable = false,
	.bufferable = false,
};
cy_stc_dma_crc_config_t TxDMA_crcConfig = 
{
	.dataReverse = false,
	.dataXor = 0,
	.reminderReverse = false,
	.reminderXor = 0,
	.polynomial = 79764919,
};

