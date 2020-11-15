#include "Blaster.h"
#include "../../../../Game/Game.h"

Blaster::Blaster(const std::weak_ptr<class Game>& game)
	: EnemyTower(game, EnemyTower::Type::Blaster)
{

}

Blaster::~Blaster()
{

}

void Blaster::initailize()
{
	EnemyTower::initailize();
}

void Blaster::updateActor(float deltatime)
{

}

void Blaster::actorInput()
{

}