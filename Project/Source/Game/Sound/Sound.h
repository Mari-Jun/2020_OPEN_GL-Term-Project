#pragma once
#include <fmod.h>


class Sound {
public:
	enum class CHANNEL
	{
		bgm = 0,
		effect,
	};

	enum class Name
	{
		Game = 0,
		Edit,
		Loading,
	};

	Sound();
	~Sound() noexcept;
	FMOD_SYSTEM* System;
	FMOD_SOUND* bgmSound[2];
	FMOD_SOUND* effectSound[2];
	FMOD_CHANNEL* Channel[2];

	void initalize();

	const int getindex();
	void setindex(int);
	void play(int,int);
protected:
	int index;
};