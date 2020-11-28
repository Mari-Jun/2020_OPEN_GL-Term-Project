#include "DefaultMinion.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "MinionAi/MinionManager.h"
#include "MinionAi/MinionAi.h"

DefaultMinion::DefaultMinion(const std::weak_ptr<class Scene>& scene, PlayerInfo info, const std::weak_ptr<class MinionManager>& manager)
	: MovePlayer(scene, info)
	, mManager(manager)
{
	setStat(info);
}

DefaultMinion::~DefaultMinion()
{

}

void DefaultMinion::initailize()
{
	MovePlayer::initailize();
}

void DefaultMinion::updateActor(float deltatime)
{
	MovePlayer::updateActor(deltatime);
	updateAnimation();
	if (ChangeTarget())
	{
		settingforDFS();
		moveforDFS();
	}
	SmoothRotate();

	checkHp();
}

void DefaultMinion::actorInput()
{
	mMoveComponent->setForwardSpeed(mStat.mSpeed);
}

void DefaultMinion::setStat(PlayerInfo info)
{
	mStat.mMaxHp = static_cast<float>(info.getHpStat());
	mStat.mDef = static_cast<float>(info.getDefStat());
	mStat.mSpeed = static_cast<float>(info.getSpeedStat());
	mStat.mHp = mStat.mMaxHp;
}

void DefaultMinion::checkHp()
{
	if (mStat.mHp <= 0.0f)
	{
		setState(Actor::State::Dead);
		std::cout << mManager.lock()->getLiveMinion() << std::endl;
		mManager.lock()->setLiveMinion(mManager.lock()->getLiveMinion() - 1);
		std::cout << mManager.lock()->getLiveMinion() << std::endl;
	}
}

bool DefaultMinion::ChangeTarget()
{
	Vector3 tmp = getPosition();
	//if (targetIndex != -1)
		//std::cout << "���� ��" << AiWay.lock()->getMinway()[targetIndex].first << ", " << AiWay.lock()->getMinway()[targetIndex].second << std::endl;

	auto tileSize = mManager.lock()->getMinionAi()->getTileSize();
	if (targetIndex == -1)
	{
		return true;
	}
	if (targetPos.x - tileSize / 4 < tmp.x && tmp.x < targetPos.x + tileSize / 4)
	{
		if (targetPos.z - 50 < tmp.z && tmp.z < targetPos.z + 50)
			if (targetIndex + 1 < mManager.lock()->getMinionAi()->getMinway().size() - 1)
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
		rotateToNewForwardNotY(Repos);
	}
}

void DefaultMinion::moveforDFS()
{
	auto way = mManager.lock()->getMinionAi();
	float tileSize = way->getTileSize();
	std::pair<int, int> oldtarget = way->getMinway()[targetIndex];
	target = way->getMinway()[targetIndex + 1];
	Vector3 oldtargetPos(-2000 + oldtarget.second * tileSize, 0, 2000 - oldtarget.first * tileSize);
	targetPos = Vector3(-2000 + target.second * tileSize, 0, 2000 - target.first * tileSize);

	repos = targetPos - oldtargetPos;
	repos.Normalize();
	rotateToNewForwardNotY(repos);
}

void DefaultMinion::settingforDFS()
{
	targetIndex += 1;
	if (targetIndex != 0)
		oldrepos = repos;
}