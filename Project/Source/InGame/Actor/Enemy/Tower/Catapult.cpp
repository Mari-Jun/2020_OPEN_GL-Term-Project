#include "Catapult.h"
#include "../../../../Game/Game.h"

Catapult::Catapult(const std::weak_ptr<class Game>& game)
	: EnemyTower(game, EnemyTower::Type::Catapult)
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