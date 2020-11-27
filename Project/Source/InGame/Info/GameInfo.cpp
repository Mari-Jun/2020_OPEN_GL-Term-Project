#include "GameInfo.h"

int PlayerInfo::getHpStat(Type type) const
{
	switch (type)
	{
	case PlayerInfo::Type::Control:
		switch (mHpLevel)
		{
		case 1: return 100;
		case 2: return 150;
		default: return 0;
		}
	case PlayerInfo::Type::Minion:
		switch (mHpLevel)
		{
		case 1: return 50;
		case 2: return 75;
		default: return 0;
		}
	default: return 0;
	}
}

int PlayerInfo::getDefStat(Type type) const
{
	switch (type)
	{
	case PlayerInfo::Type::Control:
		switch (mDefLevel)
		{
		case 1: return 0;
		case 2: return 2;
		default: return 0;
		}
	case PlayerInfo::Type::Minion:
		switch (mDefLevel)
		{
		case 1: return 0;
		case 2: return 1;
		default: return 0;
		}
	default: return 0;
	}
}

int PlayerInfo::getSpeedStat(Type type) const
{
	switch (type)
	{
	case PlayerInfo::Type::Control:
		switch (mSpeedLevel)
		{
		case 1: return 200;
		case 2: return 250;
		default: return 0;
		}
	case PlayerInfo::Type::Minion:
		switch (mSpeedLevel)
		{
		case 1: return 200;
		case 2: return 250;
		default: return 0;
		}
	default: return 0;
	}
}