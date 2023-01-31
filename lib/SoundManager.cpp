#include "SoundManager.h"
#pragma comment(lib,"lib/fmod/api/lib/fmodvc.lib")




SoundManager::SoundManager()
{

}



SoundManager::~SoundManager()
{
	ShutDown();
}


FSOUND_SAMPLE *  SoundManager::LoadSnd(const std::string& str, bool looped)
{
	FSOUND_SAMPLE * sample = nullptr;
	auto iter = m_SoundMap.find(str);

	if (iter == m_SoundMap.end())
	{
		int flags = 0;
		if (looped)
		{
			flags |= FSOUND_LOOP_NORMAL;
		}

		sample = FSOUND_Sample_Load(FSOUND_FREE, str.c_str(), flags, 0, 0);
		if (sample != nullptr)
		{
			m_SoundMap.insert(std::make_pair(str, sample));
		}
	}
	else
	{
		sample = iter->second;
	}
	return sample;
}


int	SoundManager::PlaySnd(FSOUND_SAMPLE *sound, float volume)
{
	if (!sound) return -1;
	if (volume <= 0) volume = 0;
	if (volume>1) volume = 1;

	int chan = FSOUND_PlaySound(volume, (FSOUND_SAMPLE*)sound);
	FSOUND_SetVolume(chan, (int)(volume * 255));
	return chan;
}

void SoundManager::StopSnd(int handle)
{
	if (handle <= 0) return;
	FSOUND_StopSound(handle);
}

void SoundManager::ChangeVolume(int handle, float volume)
{
	if (handle <= 0) return;
	if (volume <= 0) volume = 0;
	if (volume>1) volume = 1;
	FSOUND_SetVolume(handle, (int)(volume * 255));
}

void SoundManager::SetChanelGroup(float frequency)
{
	FSOUND_SetFrequency(FSOUND_FREE, frequency);
}

bool SoundManager::IsPlaying()
{
	return FSOUND_IsPlaying(1.0F);
}

void SoundManager::ShutDown()
{
	FSOUND_Close();
}