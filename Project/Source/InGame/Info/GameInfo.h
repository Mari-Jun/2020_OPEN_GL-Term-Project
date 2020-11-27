#pragma once
#include <string>

struct PlayerInfo
{
	enum class PlayerType
	{
		Control, Minion
	};
	enum class SkinType
	{
		Man,
		ManA,
		Adventure,
		Orc,
		Robot,
		Soldier,
		Woman,
		WomanA,
	};

	static constexpr int MAXHPLEVEL = 5;
	static constexpr int MAXDEFLEVEL = 5;
	static constexpr int MAXSPEEDLEVEL = 5;

	PlayerType mType;
	SkinType mSkinType;
	int mHpLevel;
	int mDefLevel;
	int mSpeedLevel;

	PlayerType getPlayerInfoType() const { return mType; }
	int getHpStat() const;
	int getDefStat() const;
	int getSpeedStat() const;
	
	std::string getSkinFileName() const;
};

struct GameInfo
{
	int mStage;
	int mCoin;
	PlayerInfo mControlInfo;
	PlayerInfo mMinionInfo;	
};
