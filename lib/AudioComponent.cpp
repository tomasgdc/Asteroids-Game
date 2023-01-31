#include "AudioComponent.h"

//FMod Includes
#include "fmod/api/inc/fmod.h"
#pragma comment(lib,"lib/fmod/api/lib/fmodvc.lib")


int AudioComponent::PlayMusic(const char *fname, float volume)
{
	if (music)
	{
		StopMusic();
	}

	music = FSOUND_Stream_Open(fname, FSOUND_LOOP_NORMAL, 0, 0);
	int chan = FSOUND_Stream_Play(FSOUND_FREE, music);

	if (volume <= 0) 
	{
		volume = 0;
	}

	if (volume > 1)
	{
		volume = 1;
	}

	FSOUND_SetVolume(chan, (int)(volume * 255));
	return chan;
}

void AudioComponent::StopMusic()
{
	if (music)
	{
		FSOUND_Stream_Close(music);
	}
	music = nullptr;
}
