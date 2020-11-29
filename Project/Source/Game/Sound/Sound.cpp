#include "Sound.h"
#include <iostream>


Sound::Sound()
{
	Sound::initalize(); 

}

Sound::~Sound()
{
	for (int i = 0; i < EFFECT_TRACK; ++i)	FMOD_Sound_Release(effectSound[i]);	// FMOD bgmSound 객체 해제
	for (int i = 0; i < BGM_TRACK; ++i)	FMOD_Sound_Release(bgmSound[i]);	// FMOD bgmSound 객체 해제
	for (int i = 0; i < effect.size(); ++i)	FMOD_Sound_Release(effect[i]);
	effect.clear();
	FMOD_System_Close(System); // FMOD system 객체 clsoe
	FMOD_System_Release(System); // FMOD system 객체 해제
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

	FMOD_RESULT  result;

	FMOD_System_Create(&System);
	FMOD_System_Init(System, 10, FMOD_INIT_NORMAL, NULL);

	result = FMOD_System_CreateSound(System, "Asset/Sound/nightcopy.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[0]);
	ERRCHECK(result,0);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Jazz.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[1]);
	ERRCHECK(result,1);
	result = FMOD_System_CreateSound(System, "Asset/Sound/sunny.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[2]);
	ERRCHECK(result, 2);

	//배경

	result = FMOD_System_CreateSound(System, "Asset/Sound/arrow1.mp3", FMOD_DEFAULT, 0, &effectSound[0]);
	ERRCHECK(result, 3);
	result = FMOD_System_CreateSound(System, "Asset/Sound/arrow2.mp3", FMOD_DEFAULT, 0, &effectSound[1]);
	ERRCHECK(result, 4);
	result = FMOD_System_CreateSound(System, "Asset/Sound/cannonball.mp3", FMOD_DEFAULT, 0, &effectSound[2]);
	ERRCHECK(result, 5);
	result = FMOD_System_CreateSound(System, "Asset/Sound/catapult.mp3", FMOD_DEFAULT, 0, &effectSound[3]);
	ERRCHECK(result, 6);
	result = FMOD_System_CreateSound(System, "Asset/Sound/laser.mp3", FMOD_DEFAULT, 0, &effectSound[4]);
	ERRCHECK(result, 7);
	//이펙트


}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//사운드 파일이 없거나 잘못된 파일이 아닌지 에러체크를 해주는 함수. 검사해보고 잘못된 파일이거나 사운드 파일이 없으면
//창에 메시지 출력. 
void Sound::ERRCHECK(FMOD_RESULT result,int num)
{
	if (result != FMOD_OK)
	{
		char str[256];
		sprintf_s(str, "FMOD error! ( %d ) %s\n", result, FMOD_ErrorString(result));
		std::cout << num << "번째 에서 문제 발생" << std::endl;
		std::cout << str << std::endl;
	}
}


void Sound::play(int channel, int name)
{
	FMOD_Channel_Stop(Channel[channel]);
	if (channel == 0)
	{
		FMOD_System_PlaySound(System, bgmSound[name], NULL, 0, &Channel[channel]);
		FMOD_Channel_SetVolume(Channel[channel], 0.2);
	}
	else
	{
		FMOD_System_PlaySound(System, effect[name], NULL, 0, &Channel[channel]);
		FMOD_Channel_SetVolume(Channel[channel], 0.2);
	}

}