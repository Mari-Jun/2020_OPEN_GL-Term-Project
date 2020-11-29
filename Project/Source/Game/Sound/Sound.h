#pragma once
#include <fmod.h>
#include <fmod_errors.h>
#include <vector>
#define BGM_TRACK 4
#define EFFECT_TRACK 4




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
		Sunny,
	};

	enum class effectName
	{
		Arrow1 = 0,
		Arrow2,
		Cannonball,
		catapult,
		laser
	};

	Sound();
	~Sound() noexcept;
	FMOD_SYSTEM* System;
	FMOD_SOUND* bgmSound[BGM_TRACK];
	FMOD_SOUND* effectSound[EFFECT_TRACK];
	FMOD_CHANNEL* Channel[2];

	std::vector<FMOD_SOUND*> effect;


	void initalize();

	void ERRCHECK(FMOD_RESULT,int);
	const int getindex();
	void setindex(int);
	void play(int, int);

protected:
	int index;

public:
	void setEffectIndex(int effectindex) { effect.resize(effectindex); }
};