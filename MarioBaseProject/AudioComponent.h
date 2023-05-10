#pragma once
#ifndef _AUDIOCOMPONENT_H
#define _AUDIOCOMPONENT_H

#include "Commons.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <String>
#include <iostream>


class AudioComponent
{
public:
	AudioComponent();
	~AudioComponent();

	bool LoadAudioFromFile(std::string path, bool looping, int Channel);
	void PlayAudio();
	void FreeAudio();
	bool m_looping;
	int m_channel;
	std::string m_audioPath;
private:
	Mix_Chunk* m_sound;
};

#endif // !_AUDIOCOMPONENT_H


