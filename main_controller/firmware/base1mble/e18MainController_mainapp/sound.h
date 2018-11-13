/*
 * sound.h
 *
 *  Created on: Sep 14, 2018
 *      Author: kmwh
 */

#ifndef SRC_SOUND_H_
#define SRC_SOUND_H_

#include "cycfg.h"

typedef enum{
	SOUND_IDLE,
	SOUND_PLAYING
}sound_state_t;

typedef enum{
	SOUND_SUCCESS,
	SOUND_ALREADY_PLAYING,
	SOUND_WAVDATA_ERROR
}sound_return_t;


extern void initAudioHW(void);

extern void soundThread(wiced_thread_arg_t arg);		//sound thread
extern sound_return_t soundPlay(const char* sound);		//play sound, argument is pointer to sound wav file
extern sound_state_t getSoundState(void);				//get the current sound state -- playing or idle
extern void abortSound(void);							//abort any currently playing sound

//Note on sounds:
//This code is written to handle wave files saved as arrays of chars, including the wave file header.
//The size of audio to play is pulled from the wave headers.
//Sounds need to be mono unsigned 8-bit PCM, 11.025khz sample rate. To create a sound in Audacity, use mono 16-bit PCM recording
//at 11.025khz Export as wav, "save as" "other uncompressed formats", header "Microsoft wave", encoding "unsigned 8-bit PCM".

#endif /* SRC_SOUND_H_ */
