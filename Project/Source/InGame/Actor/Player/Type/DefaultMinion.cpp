#include "DefaultMinion.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Component/MoveComponent.h"


#include "MinionAi/MinionAi.h"
#include <memory>

DefaultMinion::DefaultMinion(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class MinionAi>& ai)
	: 
	Player(scene),
	AiWay(ai)
{

}

DefaultMinion::~DefaultMinion()
{

}

void DefaultMinion::initailize()
{
	Player::initailize();
	setPlayerTexture("Asset/Mesh/Player/skin_robot.png");
	setMoveSpeed(200.0f);		
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


	mMoveComponent->setForwardSpeed(getMoveSpeed());
}

bool DefaultMinion::ChangeTarget()
{
	Vector3 tmp = getPosition();
	if (targetIndex == -1)
	{
		return true;
	}
	if (targetPos.x - 50 < tmp.x && tmp.x < targetPos.x + 50)
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
			deltarepos = (repos - oldrepos) / 20.0f;
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

	/*if (flag == 0)
	{
		flag = 1;
		auto way = AiWay.lock();
		float tileSize = way->getTileSize();
		std::pair<int, int> oldtarget = way->getMinway()[targetIndex];
		target = way->getMinway()[targetIndex + 1];
		Vector3 oldtargetPos(-2000 + oldtarget.second * tileSize, 0, 2000 - oldtarget.first * tileSize);
		targetPos = Vector3(-2000 + target.second * tileSize, 0, 2000 - target.first * tileSize);

		repos = targetPos - oldtargetPos;
		repos.Normalize();
	}

	if (Vector3::Dot(repos, Repos) != 1)
	{
		if (targetIndex == 0)
		{
			Repos = repos;
		}
		else {
			deltarepos = (repos - oldrepos) / 20.0f;
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



	Vector3 tmp = getPosition();
	if (targetPos.x - 50 < tmp.x && tmp.x < targetPos.x + 50)
	{
		if (targetPos.z - 50 < tmp.z && tmp.z < targetPos.z + 50)
			if (targetIndex + 1 < AiWay.lock()->getMinway().size() - 1)
			{
				oldrepos = repos;
				targetIndex += 1;
				flag = 0;
			}

	}*/

	

}

void DefaultMinion::settingforDFS()
{
	targetIndex += 1;
	flag = 0;
	if (targetIndex != 0)
		oldrepos = repos;
}