#ifndef ADD_MUSIC_H
#define ADD_MUSIC_H

#include <SDL.h>
#include<iostream>

class Music {
public:

	 Uint8 * audio_buf; 
	 Uint32  audio_len; 
	SDL_AudioDeviceID device_id;
	 Uint32 audio_pos = 0; 

	void initializeAudio();

	static void callback(void* userdata, Uint8* stream, int len);

	void play_wav();

	void deinit();

};

#endif