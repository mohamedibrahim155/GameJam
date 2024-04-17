#pragma once
#include "AudioManager.h"

class AudioSystem
{
public:

	AudioSystem();
	~AudioSystem();
	void LoadAudio();
	void PlayAudio();
	void PlayBGAudio();
	void StopAudio(int channelId);
	void Cleanup();

	AudioManager* audioManager = new AudioManager();
};

