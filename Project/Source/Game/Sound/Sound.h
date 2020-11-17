#pragma once
#include <fmod.h>
#include <fmod_errors.h>
#define BGM_TRACK 2
#define EFFECT_TRACK 2




class Sound {
public:
	enum class CHANNEL
	{
		bgm = 0,
		effect,
	};

	enum class bgmName
	{
		Game = 0,
		Edit,
		Loading,
	};

	enum class effectName
	{

	};

	Sound();
	~Sound() noexcept;
	FMOD_SYSTEM* System;
	FMOD_SOUND* bgmSound[BGM_TRACK];
	FMOD_SOUND* effectSound[EFFECT_TRACK];
	FMOD_CHANNEL* Channel[2];

	void initalize();

	void ERRCHECK(FMOD_RESULT,int);
	const int getindex();
	void setindex(int);
	void play(int, int);
protected:
	int index;
};