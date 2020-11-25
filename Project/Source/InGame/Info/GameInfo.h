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
	PlayerInfo mControlInfo;
	PlayerInfo mMinionInfo;	
};
