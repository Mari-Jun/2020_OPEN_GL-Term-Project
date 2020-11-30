#include "Sound.h"
#include <iostream>


Sound::Sound()
{
	Sound::initalize(); 

}

Sound::~Sound()
{
	for (int i = 0; i < EFFECT_TRACK; ++i)	FMOD_Sound_Release(effectSound[i]);	// FMOD bgmSound ��ü ����
	for (int i = 0; i < BGM_TRACK; ++i)	FMOD_Sound_Release(bgmSound[i]);	// FMOD bgmSound ��ü ����
	for (int i = 0; i < UI_TRACK; ++i) FMOD_Sound_Release(uiSound[i]);	//FMOD buttonSound ��ü ����
	FMOD_System_Close(System); // FMOD system ��ü clsoe
	FMOD_System_Release(System); // FMOD system ��ü ����
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
	//���� �߰��Ҷ� �� ��������� define TRACK �ø�����
	FMOD_RESULT  result;

	FMOD_System_Create(&System);
	FMOD_System_Init(System, 10, FMOD_INIT_NORMAL, NULL);

	result = FMOD_System_CreateSound(System, "Asset/Sound/nightcopy.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[0]);
	ERRCHECK(result,0);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Jazz.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[1]);
	ERRCHECK(result,1);
	result = FMOD_System_CreateSound(System, "Asset/Sound/sunny.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[2]);
	ERRCHECK(result, 2);

	//���

	result = FMOD_System_CreateSound(System, "Asset/Sound/Blip.wav", FMOD_DEFAULT, 0, &uiSound[0]);
	ERRCHECK(result, 3);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Blip_chat.ogg", FMOD_DEFAULT, 0, &uiSound[1]);
	ERRCHECK(result, 4);
	result = FMOD_System_CreateSound(System, "Asset/Sound/DlgNotice.mp3", FMOD_DEFAULT, 0, &uiSound[2]);
	ERRCHECK(result, 5);
	//��ư 

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
	//����Ʈ


}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//���� ������ ���ų� �߸��� ������ �ƴ��� ����üũ�� ���ִ� �Լ�. �˻��غ��� �߸��� �����̰ų� ���� ������ ������
//â�� �޽��� ���. 
void Sound::ERRCHECK(FMOD_RESULT result,int num)
{
	if (result != FMOD_OK)
	{
		char str[256];
		sprintf_s(str, "FMOD error! ( %d ) %s\n", result, FMOD_ErrorString(result));
		std::cout << num << "��° ���� ���� �߻�" << std::endl;
		std::cout << str << std::endl;
	}
}

//����, bgm�� ������ channel�� 0�� button�� ������ channel 1�� notice�� 2 effect�� effectindex�� �����ñ�
void Sound::play(int type, int name,int channel)
{
	if (type == static_cast<int>(Type::bgm))
	{
		FMOD_Channel_Stop(Channel[channel]);
		FMOD_System_PlaySound(System, bgmSound[name], NULL, 0, &Channel[channel]);
		FMOD_Channel_SetVolume(Channel[channel], 0.4);
	}
	else if(type == static_cast<int>(Type::effect))
	{
		if (channel == static_cast<int>(TypeChannel::minioneffect))
		{
			FMOD_Channel_Stop(Channel[channel]);
			FMOD_System_PlaySound(System, effectSound[name], NULL, 0, &Channel[channel]);
			FMOD_Channel_SetVolume(Channel[channel], 0.2);
		}
		else
		{
			FMOD_Channel_Stop(EffectChannel[channel - 1]);
			FMOD_System_PlaySound(System, effectSound[name], NULL, 0, &EffectChannel[channel - 1]);
			FMOD_Channel_SetVolume(EffectChannel[channel - 1], 0.2);
		}
	}
	else if(type == static_cast<int>(Type::ui))
	{
		FMOD_Channel_Stop(Channel[channel]);
		FMOD_System_PlaySound(System, uiSound[name], NULL, 0, &Channel[channel]);
		FMOD_Channel_SetVolume(Channel[channel], 0.2);
	}

}