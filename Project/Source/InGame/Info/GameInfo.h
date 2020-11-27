#pragma once

struct PlayerInfo
{
	enum class Type
	{
		Control, Minion
	};

	Type mType;
	int mHpLevel;
	int mDefLevel;
	int mSpeedLevel;

	Type getPlayerInfoType() const { return mType; }
	int getHpStat() const;
	int getDefStat() const;
	int getSpeedStat() const;
};

struct GameInfo
{
	int mStage;
	int mCoin;
	PlayerInfo mControlInfo;
	PlayerInfo mMinionInfo;	
};
