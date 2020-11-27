#pragma once

struct PlayerInfo
{
	enum class Type
	{
		Control, Minion
	};

	int mHpLevel;
	int mDefLevel;
	int mSpeedLevel;

	int getHpStat(Type type) const;
	int getDefStat(Type type) const;
	int getSpeedStat(Type type) const;
};

struct GameInfo
{
	int mStage;
	int mCoin;
	PlayerInfo mControlInfo;
	PlayerInfo mMinionInfo;	
};
