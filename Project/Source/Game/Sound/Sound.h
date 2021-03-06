#pragma once
#include <fmod.h>
#include <fmod_errors.h>
#include <vector>
#include "../Math/Math.h"
#define BGM_TRACK 4
#define EFFECT_TRACK 8
#define UI_TRACK 3




class Sound {
public:
	enum class Type
	{
		bgm = 0,
		effect,
		ui,
	};

	enum class TypeChannel
	{
		bgm = 0,
		ui,
		notice,
		minioneffect,
	};

	enum class bgmName
	{
		night = 0,
		Edit,
		Sunny,
		main,
	};

	enum class uiName
	{
		select = 0,
		click,
		notice,
	};

	enum class effectName
	{
		Arrow1 = 0,
		Arrow2,
		Cannonball,
		catapult,
		laser,
		rockbroken,
		teleport,
		createminion,
	};

	Sound();
	~Sound() noexcept;
	FMOD_SYSTEM* System;
	FMOD_SOUND* bgmSound[BGM_TRACK];
	FMOD_SOUND* effectSound[EFFECT_TRACK];
	FMOD_SOUND* uiSound[UI_TRACK];
	FMOD_CHANNEL* Channel[4];	//bgm은 0 button은 1 고정 notice는 2번고정,미니언순간이동은 3번

	Vector3 listenerPos;
	std::vector<FMOD_CHANNEL*> EffectChannel;

	void initalize();

	void ERRCHECK(FMOD_RESULT,int);
	const int getindex();
	void setindex(int);
	void play(int type, int name, int channel);
	void playDist(int name, int channel, float volume);
	void setListener(const Vector3& pos);
	void stopBgmChannel(int channel) { FMOD_Channel_Stop(Channel[channel]); }
	Vector3 getListener() const { return listenerPos; }
	void updateSound() { FMOD_System_Update(System); }

protected:
	int index;
	float mBGMVolume;
	float mEffectVolume;

public:
	void BGMvolumeUP() { mBGMVolume >= 1.0f ? NULL: mBGMVolume += 0.1f; }
	void BGMvolumeDOWN() { mBGMVolume <= 0.0f ? NULL : mBGMVolume -= 0.1f;}
	void EFFECTvolumeUP() { mEffectVolume >= 1.0f ? NULL : mEffectVolume += 0.1f; }
	void EFFECTvolumeDOWN() { mEffectVolume <= 0.0f ? NULL : mEffectVolume -= 0.1f; }
	float getBGMVolume() const { return mBGMVolume; }
	float getEFFECTVolume() const { return mEffectVolume; }

	void setEffectIndex(int effectindex) { EffectChannel.resize(effectindex); }
};