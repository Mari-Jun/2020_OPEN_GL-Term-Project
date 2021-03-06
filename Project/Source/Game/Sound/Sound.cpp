#include "Sound.h"
#include <iostream>


Sound::Sound()
	:listenerPos(Vector3::Zero)
	, mBGMVolume(1.0f)
	, mEffectVolume(1.0f)
{
	Sound::initalize();

}

Sound::~Sound()
{
	for (int i = 0; i < EFFECT_TRACK; ++i)	FMOD_Sound_Release(effectSound[i]);	// FMOD bgmSound 객체 해제
	for (int i = 0; i < BGM_TRACK; ++i)	FMOD_Sound_Release(bgmSound[i]);	// FMOD bgmSound 객체 해제
	for (int i = 0; i < UI_TRACK; ++i) FMOD_Sound_Release(uiSound[i]);	//FMOD buttonSound 객체 해제
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

	//사운드 추가할땐 꼭 헤더파일의 define TRACK 늘리세요
	FMOD_RESULT  result;

	FMOD_System_Create(&System);
	FMOD_System_Init(System, 10, FMOD_INIT_NORMAL, NULL);

	result = FMOD_System_CreateSound(System, "Asset/Sound/nightcopy.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[0]);
	ERRCHECK(result, 0);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Jazz.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[1]);
	ERRCHECK(result, 1);
	result = FMOD_System_CreateSound(System, "Asset/Sound/sunny.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[2]);
	ERRCHECK(result, 2);
	result = FMOD_System_CreateSound(System, "Asset/Sound/fantasy.wav", FMOD_LOOP_NORMAL, 0, &bgmSound[3]);
	ERRCHECK(result, 3);

	//배경

	result = FMOD_System_CreateSound(System, "Asset/Sound/Blip.wav", FMOD_DEFAULT, 0, &uiSound[0]);
	ERRCHECK(result, 3);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Blip_chat.ogg", FMOD_DEFAULT, 0, &uiSound[1]);
	ERRCHECK(result, 4);
	result = FMOD_System_CreateSound(System, "Asset/Sound/DlgNotice.mp3", FMOD_DEFAULT, 0, &uiSound[2]);
	ERRCHECK(result, 5);
	//버튼 

	result = FMOD_System_CreateSound(System, "Asset/Sound/arrow1.mp3", FMOD_DEFAULT, 0, &effectSound[0]);
	ERRCHECK(result, 5);
	result = FMOD_System_CreateSound(System, "Asset/Sound/arrow2.mp3", FMOD_DEFAULT, 0, &effectSound[1]);
	ERRCHECK(result, 6);
	result = FMOD_System_CreateSound(System, "Asset/Sound/cannonball.mp3", FMOD_DEFAULT, 0, &effectSound[2]);
	ERRCHECK(result, 7);
	result = FMOD_System_CreateSound(System, "Asset/Sound/catapult.mp3", FMOD_DEFAULT, 0, &effectSound[3]);
	ERRCHECK(result, 8);
	result = FMOD_System_CreateSound(System, "Asset/Sound/laser.mp3", FMOD_DEFAULT, 0, &effectSound[4]);
	ERRCHECK(result, 9);
	result = FMOD_System_CreateSound(System, "Asset/Sound/broken.mp3", FMOD_DEFAULT, 0, &effectSound[5]);
	ERRCHECK(result, 10);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Disappear1.mp3", FMOD_DEFAULT, 0, &effectSound[6]);
	ERRCHECK(result, 11);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Regen1.mp3", FMOD_DEFAULT, 0, &effectSound[7]);
	ERRCHECK(result, 12);
	//이펙트


}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//사운드 파일이 없거나 잘못된 파일이 아닌지 에러체크를 해주는 함수. 검사해보고 잘못된 파일이거나 사운드 파일이 없으면
//창에 메시지 출력. 
void Sound::ERRCHECK(FMOD_RESULT result, int num)
{
	if (result != FMOD_OK)
	{
		char str[256];
		sprintf_s(str, "FMOD error! ( %d ) %s\n", result, FMOD_ErrorString(result));
		std::cout << num << "번째 에서 문제 발생" << std::endl;
		std::cout << str << std::endl;
	}
}

//사용법, bgm은 무조건 channel은 0임 button은 무조건 channel 1임 notice는 2 effect는 effectindex를 넣으시길
void Sound::play(int type, int name, int channel)
{
	if (type == static_cast<int>(Type::bgm))
	{
		FMOD_Channel_Stop(Channel[channel]);
		FMOD_System_PlaySound(System, bgmSound[name], NULL, 0, &Channel[channel]);
		FMOD_Channel_SetVolume(Channel[channel], mBGMVolume);
	}
	else if (type == static_cast<int>(Type::ui))
	{
		FMOD_Channel_Stop(Channel[channel]);
		FMOD_System_PlaySound(System, uiSound[name], NULL, 0, &Channel[channel]);
		FMOD_Channel_SetVolume(Channel[channel], mEffectVolume);
	}
}


void Sound::playDist(int name, int channel, float length)
{
	if (length > 1000)
		return;

	float volume = 0.0;

	volume = (1.0 - length / 1000) / 2.0;
	if (channel == static_cast<int>(TypeChannel::minioneffect))
	{
		FMOD_Channel_Stop(Channel[channel]);
		FMOD_System_PlaySound(System, effectSound[name], NULL, 0, &Channel[channel]);
		FMOD_Channel_SetVolume(Channel[channel], volume * mEffectVolume);
	}
	else
	{
		FMOD_Channel_Stop(EffectChannel[channel - 1]);
		FMOD_System_PlaySound(System, effectSound[name], NULL, 0, &EffectChannel[channel - 1]);
		FMOD_Channel_SetVolume(EffectChannel[channel - 1], volume * mEffectVolume);
	}
}


void Sound::setListener(const Vector3& Pos)
{
	listenerPos = Pos;
}