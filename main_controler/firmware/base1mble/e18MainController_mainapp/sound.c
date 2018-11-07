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

#define WAV_HEADER_SIZE 0x2C	//number of bytes to skip for wave header
#define WAV_DATASIZE_OFFSET 0x28
#define WAV_DATASIZE_SIZE 0x04

#define BIT8_SOUND

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

#ifdef SOUND_16BIT
static uint16_t* soundStartPtr;
static uint16_t* soundEndPtr;
#endif

#ifdef BIT8_SOUND
static uint8_t* soundStartPtr;
static uint8_t* soundEndPtr;
#endif


SOUND_STATE_T soundPlayerState = SOUND_IDLE;
void readWavHeader(WAV_HEADER_T* header, const uint8_t* soundArray);

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
	Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 0);		//mute amplifier
	soundPlayerState = SOUND_IDLE;
	Cy_TCPWM_Counter_SetCompare0(audioPWM_HW, audioPWM_NUM, 128);
}

SOUND_STATE_T getSoundState(void)
{
	return soundPlayerState;
}


void soundThread(wiced_thread_arg_t arg)
{
	Cy_GPIO_Write(audioMute_PORT, audioMute_PIN, 0);	//mute amplifier
    //set up audio pwm
    Cy_TCPWM_PWM_Init(audioPWM_HW, audioPWM_NUM, &audioPWM_config);
    Cy_TCPWM_PWM_Enable(audioPWM_HW, audioPWM_NUM);
    Cy_TCPWM_TriggerStart(audioPWM_HW, audioPWM_MASK);

	while(1)
	{
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



void readWavHeader(WAV_HEADER_T* header, const uint8_t* soundArray)
{
	memcpy(header, soundArray, WAV_HEADER_SIZE);
}
