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


#define BIT8_SOUND

#ifdef SOUND_16BIT
static uint16_t* soundStartPtr;
static uint16_t* soundEndPtr;
#endif

#ifdef BIT8_SOUND
static uint8_t* soundStartPtr;
static uint8_t* soundEndPtr;
#endif

 cy_stc_sysint_t audioIntrCfg =
    {
            .intrSrc = tcpwm_1_interrupts_0_IRQn, /* Interrupt source is GPIO port 0 interrupt */
            .intrPriority = 7UL                     /* Interrupt priority is 2 */
    };



SOUND_STATE_T soundPlayerState = SOUND_IDLE;


void initAudioHW(void)
{
    //audio pwm
    Cy_TCPWM_PWM_Init(audioPWM_HW, audioPWM_NUM, &audioPWM_config);
    Cy_TCPWM_PWM_Enable(audioPWM_HW, audioPWM_NUM);
    Cy_TCPWM_TriggerStart(audioPWM_HW, audioPWM_MASK);

    //audio sample interrupt
    // Cy_TCPWM_Counter_Init(audioSampleInt_HW, audioSampleInt_NUM, &audioSampleInt_config);
    // Cy_TCPWM_Counter_Enable(audioSampleInt_HW, audioSampleInt_NUM);
    // Cy_TCPWM_TriggerStart(audioSampleInt_HW, audioSampleInt_MASK);

    // Cy_TCPWM_SetInterruptMask(audioSampleInt_HW, audioSampleInt_MASK, CY_TCPWM_INT_ON_TC | Cy_TCPWM_GetInterruptMask(audioSampleInt_HW, audioSampleInt_MASK));
 	// Cy_SysInt_Init(&audioIntrCfg, &tcpwm_1_interrupts_0_IRQn_Handler);
 	// NVIC_EnableIRQ(audioIntrCfg.intrSrc);
}



//wave file reference:   https://www.isip.piconepress.com/projects/speech/software/tutorials/production/fundamentals/v1.0/section_02/s02_01_p05.html
SOUND_RETURN_T playSound(const char* sound)
{
	WAV_HEADER_T wavHeader;
	SOUND_RETURN_T returnValue;

	if(soundPlayerState == SOUND_IDLE)
	{
		readWavHeader(&wavHeader, sound);

		Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 1);	//unmute amplifier


#ifdef SOUND_16BIT
		soundStartPtr = (uint16_t*)sound + WAV_HEADER_SIZE;
		soundEndPtr = soundStartPtr + (wavHeader.table.dataSize/2);
#endif

#ifdef BIT8_SOUND
		soundStartPtr = sound + WAV_HEADER_SIZE;
		soundEndPtr = soundStartPtr + wavHeader.table.dataSize;
#endif

		soundPlayerState = SOUND_PLAYING;

		//could do a sanity check that wave file header sample size matches array size
		//if(wavReportedSize%2) data chunk is not 16 bit
		//if(wavReportedSize != sizeof(sound) - WAV_HEADER_SIZE

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
	soundPlayerState = SOUND_IDLE;
	Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, 128);
}

SOUND_STATE_T getSoundState(void)
{
	return soundPlayerState;
}



void tcpwm_1_interrupts_0_IRQn_Handler(void)
{
//	soundTimerInterrupt();
}


void soundThread(wiced_thread_arg_t arg)
{
	while(1)
	{
		Cy_GPIO_Inv(BLUE_LED_PORT, BLUE_LED_PIN);
		if(soundPlayerState == SOUND_PLAYING)
		{
#ifdef SOUND_16BIT
			 Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, *soundStartPtr >> 7);
#endif

#ifdef BIT8_SOUND
			 Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, *soundStartPtr);
#endif
			soundStartPtr++;
			if(soundStartPtr == soundEndPtr)
			{
				Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 0);		//mute amplifier

#ifdef BIT8_SOUND
			 Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, 128);
#endif
				soundPlayerState = SOUND_IDLE;
			}
		}
		
		wiced_rtos_delay_microseconds(100);
	}
}


//this interrupt needs to happen at the wave sample rate
void soundTimerInterrupt(void)
{
	uint32_t intr = Cy_TCPWM_GetInterruptStatusMasked(audioSampleInt_HW, audioSampleInt_NUM);
//	if(intr > 0)
//	{
//		Cy_SCB_UART_Put(SCB5, intr + 0x30);
//	}

	if(intr == CY_TCPWM_INT_ON_TC)
	{
		//Cy_GPIO_Inv(GREEN_LED_PORT, GREEN_LED_PIN);
		if(soundPlayerState == SOUND_PLAYING)
		{

			//pwmValue = *soundStartPtr >> 6;
#ifdef SOUND_16BIT
			 Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, *soundStartPtr >> 7);
#endif

#ifdef BIT8_SOUND
			 Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, *soundStartPtr);
#endif
			 //soundPWM = *soundStartPtr;
			soundStartPtr++;
			if(soundStartPtr == soundEndPtr)
			{
				Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 1);		//mute amplifier

#ifdef BIT8_SOUND
			 Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, 128);
#endif
				soundPlayerState = SOUND_IDLE;
			}
		}
	}
	Cy_TCPWM_ClearInterrupt(audioSampleInt_HW, audioSampleInt_NUM, intr);
}

void readWavHeader(WAV_HEADER_T* header, const uint8_t* soundArray)
{
	memcpy(header, soundArray, WAV_HEADER_SIZE);
}
