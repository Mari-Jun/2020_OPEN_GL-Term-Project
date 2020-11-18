#include "Blaster.h"
#include "../../../../Game/Game.h"

Blaster::Blaster(const std::weak_ptr<class Scene>& scene)
	: Weapon(scene)
{

}

Blaster::~Blaster()
{

}

void Blaster::initailize()
{
	Weapon::initailize();
}

void Blaster::updateActor(float deltatime)
{

}

void Blaster::actorInput()
{

}

void Blaster::attack()
{

}

void Blaster::attackMotion()
{

}