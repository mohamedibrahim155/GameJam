#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	audioManager->Initialize();
	LoadAudio();
}

AudioSystem::~AudioSystem()
{
	Cleanup();
}

void AudioSystem::LoadAudio()
{
	audioManager->Load3DAudio("Audio/Footsteps.wav");
	audioManager->Load3DAudio("Audio/assassins.mp3");
	
}

void AudioSystem::PlayAudio()
{
	 audioManager->PlayAudio("Audio/Footsteps.wav", 1);
}

void AudioSystem::PlayBGAudio()
{
     audioManager->PlayAudio("Audio/assassins.mp3", 2);
}

void AudioSystem::StopAudio(int channelId)
{
	audioManager->SetChannelStop(channelId);
}

void AudioSystem::Cleanup()
{
	assert(audioManager);
	audioManager->Destroy();
}
