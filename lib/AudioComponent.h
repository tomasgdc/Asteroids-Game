#pragma once

//Forward declaration
struct FSOUND_STREAM;

class AudioComponent
{
public:
	// returns a handle which you only need if you want to change volume later with ChangeVolume
	int		PlayMusic(const char *fname, float volume = 1);

	void	StopMusic();
private:
	FSOUND_STREAM *music;
};