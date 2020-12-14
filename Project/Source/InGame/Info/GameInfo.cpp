#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameInfo.h"

int PlayerInfo::getHpStat() const
{
	switch (mType)
	{
	case PlayerInfo::PlayerType::Control:
		switch (mHpLevel)
		{
		case 1: return 100;
		case 2: return 150;
		case 3: return 200;
		case 4: return 250;
		case 5: return 300;
		default: return 0;
		}
	case PlayerInfo::PlayerType::Minion:
		switch (mHpLevel)
		{
		case 1: return 50;
		case 2: return 75;
		case 3: return 100;
		case 4: return 125;
		case 5: return 150;
		default: return 0;
		}
	default: return 0;
	}
}

int PlayerInfo::getDefStat() const
{
	switch (mType)
	{
	case PlayerInfo::PlayerType::Control:
		switch (mDefLevel)
		{
		case 1: return 0;
		case 2: return 2;
		case 3: return 4;
		case 4: return 6;
		case 5: return 8;
		default: return 0;
		}
	case PlayerInfo::PlayerType::Minion:
		switch (mDefLevel)
		{
		case 1: return 0;
		case 2: return 1;
		case 3: return 2;
		case 4: return 3;
		case 5: return 4;
		default: return 0;
		}
	default: return 0;
	}
}

int PlayerInfo::getSpeedStat() const
{
	switch (mType)
	{
	case PlayerInfo::PlayerType::Control:
		switch (mSpeedLevel)
		{
		case 1: return 200;
		case 2: return 110;
		case 3: return 120;
		case 4: return 135;
		case 5: return 150;
		default: return 0;
		}
	case PlayerInfo::PlayerType::Minion:
		switch (mSpeedLevel)
		{
		case 1: return 200;
		case 2: return 110;
		case 3: return 120;
		case 4: return 135;
		case 5: return 150;
		default: return 0;
		}
	default: return 0;
	}
}

std::string PlayerInfo::getSkinFileName() const
{
	switch (mSkinType)
	{
	case PlayerInfo::SkinType::Man: return "Asset/Mesh/Player/skin_man.png";
	case PlayerInfo::SkinType::ManA: return "Asset/Mesh/Player/skin_manAlternative.png";
	case PlayerInfo::SkinType::Adventure: return "Asset/Mesh/Player/skin_adventurer.png";
	case PlayerInfo::SkinType::Orc: return "Asset/Mesh/Player/skin_orc.png";
	case PlayerInfo::SkinType::Robot: return "Asset/Mesh/Player/skin_robot.png";
	case PlayerInfo::SkinType::Soldier: return "Asset/Mesh/Player/skin_soldier.png";
	case PlayerInfo::SkinType::Woman: return "Asset/Mesh/Player/skin_woman.png";
	case PlayerInfo::SkinType::WomanA: return "Asset/Mesh/Player/skin_womanAlternative.png";
	default: return "";
	}
}

void  PlayerInfo::setSkin(const std::string& fileName)
{
	if (fileName == "Asset/Mesh/Player/skin_man.png")
	{
		mSkinType = SkinType::Man;
	}
	else if (fileName == "Asset/Mesh/Player/skin_manAlternative.png")
	{
		mSkinType = SkinType::ManA;
	}
	else if (fileName == "Asset/Mesh/Player/skin_adventurer.png")
	{
		mSkinType = SkinType::Adventure;
	}
	else if (fileName == "Asset/Mesh/Player/skin_orc.png")
	{
		mSkinType = SkinType::Orc;
	}
	else if (fileName == "Asset/Mesh/Player/skin_robot.png")
	{
		mSkinType = SkinType::Robot;
	}
	else if (fileName == "Asset/Mesh/Player/skin_soldier.png")
	{
		mSkinType = SkinType::Soldier;
	}
	else if (fileName == "Asset/Mesh/Player/skin_woman.png")
	{
		mSkinType = SkinType::Woman;
	}
	else if (fileName == "Asset/Mesh/Player/skin_womanAlternative.png")
	{
		mSkinType = SkinType::WomanA;
	}
}

void PlayerInfo::changeSkinType(bool next)
{
	switch (mSkinType)
	{
	case PlayerInfo::SkinType::Man: next ? mSkinType = SkinType::ManA : mSkinType = SkinType::Man; break;
	case PlayerInfo::SkinType::ManA: next ? mSkinType = SkinType::Adventure : mSkinType = SkinType::Man; break;
	case PlayerInfo::SkinType::Adventure: next ? mSkinType = SkinType::Orc : mSkinType = SkinType::ManA; break;
	case PlayerInfo::SkinType::Orc: next ? mSkinType = SkinType::Robot : mSkinType = SkinType::Adventure; break;
	case PlayerInfo::SkinType::Robot: next ? mSkinType = SkinType::Soldier : mSkinType = SkinType::Orc; break;
	case PlayerInfo::SkinType::Soldier: next ? mSkinType = SkinType::Woman : mSkinType = SkinType::Robot; break;
	case PlayerInfo::SkinType::Woman: next ? mSkinType = SkinType::WomanA : mSkinType = SkinType::Soldier; break;
	case PlayerInfo::SkinType::WomanA: next ? mSkinType = SkinType::WomanA : mSkinType = SkinType::Woman; break;
	default: break;
	}
}

bool GameInfo::saveGameInfo()
{
	std::string fileName = "SaveFile/file.bin";
	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "file not found : " << fileName << '\n';
		return false;
	}

	file << "Stage " << mStage << '\n';
	file << "Coin " << mCoin << '\n';
	file << "Control " << mControlInfo.mHpLevel << " " << mControlInfo.mDefLevel << " " << mControlInfo.mSpeedLevel << " " << mControlInfo.getSkinFileName() << '\n';
	file << "Minion " << mMinionInfo.mHpLevel << " " << mMinionInfo.mDefLevel << " " << mMinionInfo.mSpeedLevel << " " << mMinionInfo.getSkinFileName() << '\n';

	std::cerr << fileName << " Save complete\n";
	return true;
}

bool GameInfo::loadGameInfo()
{
	std::string fileName = "SaveFile/file.bin";
	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "file not found : " << fileName << '\n';
		return false;
	}

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	std::string skin;

	while (std::getline(file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "Stage")
		{
			ss >> mStage;
		}
		else if (prefix == "Coin")
		{
			ss >> mCoin;
		}
		else if (prefix == "Control")
		{
			ss >> mControlInfo.mHpLevel >> mControlInfo.mDefLevel >> mControlInfo.mSpeedLevel >> skin;
			mControlInfo.setSkin(skin);
			mControlInfo.mType = PlayerInfo::PlayerType::Control;
		}
		else if (prefix == "Minion")
		{
			ss >> mMinionInfo.mHpLevel >> mMinionInfo.mDefLevel >> mMinionInfo.mSpeedLevel >> skin;
			mMinionInfo.setSkin(skin);
			mMinionInfo.mType = PlayerInfo::PlayerType::Minion;
		}
	}

	std::cerr << fileName << " load complete\n";
	return true;
}