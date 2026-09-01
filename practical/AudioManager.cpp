#include "AudioManager.h"
void AudioManager::InitializeAudio()
{
	result = FMOD::System_Create(&system); //create sound card
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata); //initialize with 32 channels
}

void AudioManager::PlayGunShot()
{									//channel group can group sounds,			pause   fmod return what sound	channel
	result = system->playSound(gunShot, 0,										true,			&channel);
	channel->setPan(gunShotPan);
	channel->setPaused(false);
	channel->setPitch(2);

}	

void AudioManager::PlaySoundtrack()
{
	result = system->playSound(bgm, 0, true, &channel);
}

void AudioManager::LoadSounds()
{
	result = system->createSound("Assets/bullet2.mp3", FMOD_DEFAULT, 0, &gunShot);
	result = gunShot->setMode(FMOD_LOOP_OFF);

	result = system->createStream("Assets/bgm.mp3", FMOD_DEFAULT, 0, &bgm);
	result = bgm->setMode(FMOD_LOOP_OFF);
}

void AudioManager::UpdateSound()
{
	result = system->update();
}
void AudioManager::Pause() {
	channel->setPaused(true);
	PlaySoundtrack();
}
void AudioManager::Unpause() {
	channel->setPaused(false);
}

