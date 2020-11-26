#pragma once

struct PlayerInfo
{
	int mHpLevel;
	int mDefLevel;
	int mSpeedLevel;
};

struct GameInfo
{
	int mStage;
	int mCoin;
	PlayerInfo mControlInfo;
	PlayerInfo mMinionInfo;	
};
