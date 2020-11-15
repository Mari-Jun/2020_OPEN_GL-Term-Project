#include "Ballista.h"
#include "../../../../Game/Game.h"

Ballista::Ballista(const std::weak_ptr<class Game>& game)
	: EnemyTower(game, EnemyTower::Type::Ballista)
{

}

Ballista::~Ballista()
{

}

void Ballista::initailize()
{
	EnemyTower::initailize();
}

void Ballista::updateActor(float deltatime)
{
	
}

void Ballista::actorInput()
{

}