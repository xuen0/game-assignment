#pragma once
#include "fmod.hpp"
class AudioManager
{
public:
	FMOD::System* system; // virtual sound system / sound card
	FMOD::Sound* gunShot, * bgm; // sound files
	float gunShotPan = 0.0, sound2Pan = 0.0;
	FMOD::Channel* channel = 0; //cannot choose channel with fmod, fmod choose automatically which available, can use to modify volume (without modifying the original audio)
	FMOD_RESULT result;
	void* extradriverdata = 0;

	void InitializeAudio();
	void PlayGunShot();
	void PlaySoundtrack();
	void LoadSounds();
	void UpdateSound();
	void Pause();
	void Unpause();
};

