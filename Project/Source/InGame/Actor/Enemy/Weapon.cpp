#include "Weapon.h"
#include "../../../Game/Game.h"

Weapon::Weapon(const std::weak_ptr<class Scene>& scene)
	: Actor(scene)
	, mAttackDelay(1.0f)
	, mCurDelay(mAttackDelay)
	, mAttackRange(500.0f)
{

}

Weapon::~Weapon()
{
	
}

void Weapon::initailize()
{
	Actor::initailize();


}

void Weapon::setEffectIndex(int index)
{

}

void Weapon::updateActor(float deltatime)
{

}

void Weapon::actorInput()
{

}

void Weapon::attack()
{

}

void Weapon::attackMotion()
{

}