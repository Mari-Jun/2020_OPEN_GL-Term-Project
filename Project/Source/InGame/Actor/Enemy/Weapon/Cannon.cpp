#include "Cannon.h"
#include "../../../../Game/Game.h"

Cannon::Cannon(const std::weak_ptr<class Scene>& scene)
	: Weapon(scene)
{

}

Cannon::~Cannon()
{

}

void Cannon::initailize()
{
	Weapon::initailize();
}

void Cannon::updateActor(float deltatime)
{

}

void Cannon::actorInput()
{

}

void Cannon::attack()
{

}

void Cannon::attackMotion()
{

}