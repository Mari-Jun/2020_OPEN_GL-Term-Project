#include "Cannon.h"
#include "../../../../Game/Game.h"

Cannon::Cannon(const std::weak_ptr<class Game>& game)
	: EnemyTower(game, EnemyTower::Type::Cannon)
{

}

Cannon::~Cannon()
{

}

void Cannon::initailize()
{
	EnemyTower::initailize();
}

void Cannon::updateActor(float deltatime)
{

}

void Cannon::actorInput()
{

}