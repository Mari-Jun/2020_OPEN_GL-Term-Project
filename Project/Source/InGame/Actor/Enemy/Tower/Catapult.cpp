#include "Catapult.h"
#include "../../../../Game/Game.h"

Catapult::Catapult(const std::weak_ptr<class Scene>& scene)
	: EnemyTower(scene, EnemyTower::Type::Catapult)
{

}

Catapult::~Catapult()
{

}

void Catapult::initailize()
{
	EnemyTower::initailize();
}

void Catapult::updateActor(float deltatime)
{

}

void Catapult::actorInput()
{

}