#include "Sound.h"
#include <iostream>


Sound::Sound()
{
	Sound::initalize();
}

Sound::~Sound()
{
	for (int i = 0; i < 2; ++i)	FMOD_Sound_Release(effectSound[i]);	// FMOD bgmSound °´Ã¼ ÇØÁ¦
	for (int i = 0; i < 2; ++i)	FMOD_Sound_Release(bgmSound[i]);	// FMOD bgmSound °´Ã¼ ÇØÁ¦
	FMOD_System_Close(System); // FMOD system °´Ã¼ clsoe
	FMOD_System_Release(System); // FMOD system °´Ã¼ ÇØÁ¦
}


const int Sound::getindex()
{
	return index;
}

void Sound::setindex(int i)
{
	index = i;
}

void Sound::initalize()
{
	index = 0;
	char string[100];

	FMOD_System_Create(&System);
	FMOD_System_Init(System, 10, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(System, "Asset/Sound/nightcopy.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[0]);
	FMOD_System_CreateSound(System, "Asset/Sound/Jazz_For_Dr_Lim.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[1]);

	//¹è°æ

	//FMOD_System_CreateSound(System, "effect", FMOD_DEFAULT, 0, &effectSound);
	//ÀÌÆåÆ®
	

}

void Sound::play(int channel,int name)
{
	FMOD_Channel_Stop(Channel[channel]);
	FMOD_System_PlaySound(System, bgmSound[name], NULL, 0, &Channel[channel]);
	FMOD_Channel_SetVolume(Channel[channel], 0.2);

}