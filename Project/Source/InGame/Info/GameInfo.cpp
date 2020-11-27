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
		default: return 0;
		}
	case PlayerInfo::PlayerType::Minion:
		switch (mDefLevel)
		{
		case 1: return 0;
		case 2: return 1;
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
		case 2: return 250;
		default: return 0;
		}
	case PlayerInfo::PlayerType::Minion:
		switch (mSpeedLevel)
		{
		case 1: return 200;
		case 2: return 250;
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