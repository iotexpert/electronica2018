/*
 * sound.h
 *
 *  Created on: Sep 14, 2018
 *      Author: kmwh
 */

#ifndef SRC_SOUND_H_
#define SRC_SOUND_H_

//#include "wiced.h"
#include "cycfg.h"


#define WAV_HEADER_SIZE 0x2C	//number of bytes to skip for wave header
#define WAV_DATASIZE_OFFSET 0x28
#define WAV_DATASIZE_SIZE 0x04

typedef enum{
	SOUND_IDLE,
	SOUND_PLAYING
}SOUND_STATE_T;

typedef enum{
	SOUND_SUCCESS,
	SOUND_ALREADY_PLAYING,
	SOUND_WAVDATA_ERROR
}SOUND_RETURN_T;


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

extern void soundThread(wiced_thread_arg_t arg);
extern void initAudioHW(void);
extern SOUND_RETURN_T playSound(const char* sound);
extern SOUND_STATE_T getSoundState(void);
void readWavHeader(WAV_HEADER_T* header, const uint8_t* soundArray);
void soundTimerInterrupt(void);


#endif /* SRC_SOUND_H_ */
