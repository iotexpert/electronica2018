/*******************************************************************************
* File Name: cycfg_dmas.h
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

#if !defined(CYCFG_DMAS_H)
#define CYCFG_DMAS_H

#include "cycfg_notices.h"
#include "cy_dma.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define TxDMA_HW DW0
#define TxDMA_CHANNEL 5
#define TxDMA_IRQ cpuss_interrupts_dw0_5_IRQn

extern cy_stc_dma_descriptor_config_t TxDMA_Descriptor_0_config;
extern cy_stc_dma_descriptor_t TxDMA_Descriptor_0;
extern cy_stc_dma_channel_config_t TxDMA_channelConfig;
extern cy_stc_dma_crc_config_t TxDMA_crcConfig;


#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_DMAS_H */