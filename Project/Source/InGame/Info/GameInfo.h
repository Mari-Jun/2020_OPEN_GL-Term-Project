#pragma once

struct PlayerInfo
{
	enum class Type
	{
		Control, Minion
	};

	static constexpr int MAXHPLEVEL = 5;
	static constexpr int MAXDEFLEVEL = 5;
	static constexpr int MAXSPEEDLEVEL = 5;

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
