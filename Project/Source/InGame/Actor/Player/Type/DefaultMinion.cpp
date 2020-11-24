#include "DefaultMinion.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Component/MoveComponent.h"


#include "MinionAi/MinionAi.h"
#include <memory>

DefaultMinion::DefaultMinion(const std::weak_ptr<class Scene>& scene, PlayerInfo info, const std::weak_ptr<class MinionAi>& ai)
	: Player(scene, info, PlayerType::Defualt)
	, AiWay(ai)
{
	setStat(info);
}

DefaultMinion::~DefaultMinion()
{

}

void DefaultMinion::initailize()
{
	Player::initailize();
	setPlayerTexture("Asset/Mesh/Player/skin_robot.png");
}

void DefaultMinion::updateActor(float deltatime)
{
	Player::updateActor(deltatime);
	if (ChangeTarget())
	{
		settingforDFS();
		moveforDFS();
	}
	SmoothRotate();
}

void DefaultMinion::actorInput()
{
	auto game = getGame().lock();

	mMoveComponent->setForwardSpeed(mStat.mSpeed);
}

void DefaultMinion::setStat(PlayerInfo info)
{
	switch (info.mHpLevel)
	{
	case 1: mStat.mMaxHp = 100.0f; break;
	default: break;
	}

	switch (info.mDefLevel)
	{
	case 1: mStat.mDef = 0.0f; break;
	default: break;
	}

	switch (info.mSpeedLevel)
	{
	case 1: mStat.mSpeed = 200.0f; break;
	default: break;
	}
}


bool DefaultMinion::ChangeTarget()
{
	Vector3 tmp = getPosition();
	if (targetIndex == -1)
	{
		return true;
	}
	if (targetPos.x - AiWay.lock()->getTileSize() / 4 < tmp.x && tmp.x < targetPos.x + AiWay.lock()->getTileSize() / 4)
	{
		if (targetPos.z - 50 < tmp.z && tmp.z < targetPos.z + 50)
			if (targetIndex + 1 < AiWay.lock()->getMinway().size() - 1)
			{
				return true;
			}

	}
	return false;

}

void DefaultMinion::SmoothRotate()
{
	if (Vector3::Dot(repos, Repos) != 1)
	{
		if (targetIndex == 0)
		{
			Repos = repos;
		}
		else {
			deltarepos = (repos - oldrepos) / MINION_ANGLE;
			Repos += deltarepos;
			Repos.Normalize();
			if (Vector3::Dot(repos, Repos) > 0.99 || Vector3::Dot(repos, Repos) < -0.99)
			{
				Repos = repos;
				Vector3::Dot(repos, Repos);
			}
		}


		rotateToNewForward(Repos);
	}
}

void DefaultMinion::moveforDFS()
{
	auto way = AiWay.lock();
	float tileSize = way->getTileSize();
	std::pair<int, int> oldtarget = way->getMinway()[targetIndex];
	target = way->getMinway()[targetIndex + 1];
	Vector3 oldtargetPos(-2000 + oldtarget.second * tileSize, 0, 2000 - oldtarget.first * tileSize);
	targetPos = Vector3(-2000 + target.second * tileSize, 0, 2000 - target.first * tileSize);

	repos = targetPos - oldtargetPos;
	repos.Normalize();
	rotateToNewForward(repos);

	targetIndex += 1;
}

void DefaultMinion::settingforDFS()
{
	targetIndex += 1;
	if (targetIndex != 0)
		oldrepos = repos;
}