/*
 * sound.c
 *
 *  Created on: Sep 14, 2018
 *      Author: kmwh
 */

#include "wiced.h"
#include "cy_pdl.h"
#include "sound.h"
#include "string.h"
#include "cycfg.h"
#include "cycfg_pins.h"

#include "platform_isr_interface.h"			//needed for interrupt definition


#define WAV_HEADER_SIZE 0x2C	//number of bytes to skip for wave header
#define WAV_DATASIZE_OFFSET 0x28
#define WAV_DATASIZE_SIZE 0x04

typedef struct{
	uint8_t riffStr[4];
	uint32_t riffSize;
	uint8_t wavStr[4];
	uint8_t fmtStr[4];
	uint32_t wavChunk;
	uint16_t wavFormat;
	uint16_t wavMonoStereo;
	uint32_t sampleFrequency;
	uint32_t byteRate;
	uint16_t blockAlignment;
	uint16_t bitsPerSample;
	uint8_t dataStr[4];
	uint32_t dataSize;
}WAV_TABLE_T;


typedef union{
	WAV_TABLE_T table;
	uint8_t fullHeader[WAV_HEADER_SIZE];
}WAV_HEADER_T;


enum{
	AMP_MUTED = 0,
	AMP_ON = 1
};

//for DMA interrupt     cpuss_interrupts_dw0_5_IRQn
 cy_stc_sysint_t dmaIntrCfg =
    {
            .intrSrc = cpuss_interrupts_dw0_5_IRQn, /* Interrupt source is GPIO port 0 interrupt */
            .intrPriority = 7UL                     /* Interrupt priority is 2 */
    };


sound_state_t soundPlayerState = SOUND_IDLE;
void readWavHeader(WAV_HEADER_T* header, const uint8_t* soundArray);

void initAudioHW(void)
{
	Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, AMP_MUTED);		//mute amplifier

    //audio pwm
    Cy_TCPWM_PWM_Init(audioPWM_HW, audioPWM_NUM, &audioPWM_config);
    Cy_TCPWM_PWM_Enable(audioPWM_HW, audioPWM_NUM);
    Cy_TCPWM_TriggerStart(audioPWM_HW, audioPWM_MASK);
				
    //audio sample interrupt
    Cy_TCPWM_Counter_Init(audioSampleInt_HW, audioSampleInt_NUM, &audioSampleInt_config);
    Cy_TCPWM_Counter_Enable(audioSampleInt_HW, audioSampleInt_NUM);

  	Cy_DMA_Channel_SetInterruptMask (DW0, 5UL, CY_DMA_INTR_MASK);
 	Cy_SysInt_Init(&dmaIntrCfg, &cpuss_interrupts_dw0_5_IRQn_Handler);
 	NVIC_EnableIRQ(dmaIntrCfg.intrSrc);
}


//when the dma interrupt fires...
void cpuss_interrupts_dw0_5_IRQn_Handler(void)
{
	soundPlayerState = SOUND_IDLE;							//we are done with the sound
	Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 0);		//mute amplifier
	Cy_DMA_Channel_Disable(TxDMA_HW, TxDMA_CHANNEL);
	Cy_DMA_Channel_ClearInterrupt(DW0, 5UL);
}


//wave file reference:   https://www.isip.piconepress.com/projects/speech/software/tutorials/production/fundamentals/v1.0/section_02/s02_01_p05.html
sound_return_t soundPlay(const char* sound)
{
	WAV_HEADER_T wavHeader;
	sound_return_t returnValue;
	uint8_t* soundStartPtr;

	if(soundPlayerState == SOUND_IDLE)
	{
		readWavHeader(&wavHeader, sound);
		soundStartPtr = sound + WAV_HEADER_SIZE;

		//for DMA
    	TxDMA_Descriptor_0_config.srcAddress = soundStartPtr;
    	TxDMA_Descriptor_0_config.dstAddress = (uint32_t *) &TCPWM1_CNT2->CC;
		TxDMA_Descriptor_0_config.yCount = wavHeader.table.dataSize/256;
    	Cy_DMA_Descriptor_Init(&TxDMA_Descriptor_0, &TxDMA_Descriptor_0_config);
    	Cy_DMA_Channel_Init(TxDMA_HW, TxDMA_CHANNEL, &TxDMA_channelConfig);
    	Cy_DMA_Channel_SetDescriptor(TxDMA_HW, TxDMA_CHANNEL, &TxDMA_Descriptor_0);
    	Cy_DMA_Channel_Enable(TxDMA_HW, TxDMA_CHANNEL);
		Cy_DMA_Enable(TxDMA_HW);


		Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 1);	//unmute amplifier
		Cy_TCPWM_TriggerStart(audioSampleInt_HW, audioSampleInt_MASK);

		soundPlayerState = SOUND_PLAYING;
		returnValue = SOUND_SUCCESS;
	}
	else
	{
		returnValue = SOUND_ALREADY_PLAYING;
	}
		return returnValue;
}

void abortSound(void)
{
	Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 0);		//mute amplifier
	soundPlayerState = SOUND_IDLE;
	Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, 128);
}

sound_state_t getSoundState(void)
{
	return soundPlayerState;
}



void readWavHeader(WAV_HEADER_T* header, const uint8_t* soundArray)
{
	memcpy(header, soundArray, WAV_HEADER_SIZE);
}

