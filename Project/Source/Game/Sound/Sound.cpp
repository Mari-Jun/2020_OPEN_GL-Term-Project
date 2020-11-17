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

	FMOD_RESULT  result;

	FMOD_System_Create(&System);
	FMOD_System_Init(System, 10, FMOD_INIT_NORMAL, NULL);

	result = FMOD_System_CreateSound(System, "Asset/Sound/nightcopy.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[0]);
	ERRCHECK(result,0);
	result = FMOD_System_CreateSound(System, "Asset/Sound/Jazz.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[1]);
	ERRCHECK(result,1);

	//���

	//FMOD_System_CreateSound(System, "effect", FMOD_DEFAULT, 0, &effectSound);
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


void Sound::play(int channel, int name)
{
	FMOD_Channel_Stop(Channel[channel]);
	FMOD_System_PlaySound(System, bgmSound[name], NULL, 0, &Channel[channel]);
	FMOD_Channel_SetVolume(Channel[channel], 0.2);

}