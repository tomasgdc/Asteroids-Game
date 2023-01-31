#pragma once

//FMod Includes
#include "fmod/api/inc/fmod.h"
#include <unordered_map>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	// if you set loop the sample will go on looping forever, until you call StopSound
	FSOUND_SAMPLE *  LoadSnd(const std::string& str, bool loop = false);

	// returns a handle which you only need if you are going to call StopSound or ChangeVolume()
	 int	PlaySnd(FSOUND_SAMPLE *sound, float volume = 1);

	 void	StopSnd(int handle);

	 void	ChangeVolume(int handle, float newvolume = 1);

	 void   SetChanelGroup(float frequency);

	 bool   IsPlaying();
 protected:
	 void ShutDown();

private:
	
	std::unordered_map<std::string, FSOUND_SAMPLE*> m_SoundMap;
};