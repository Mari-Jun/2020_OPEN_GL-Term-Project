#include "Blaster.h"
#include "../Projectile/Arrow.h"
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
	Weapon::updateActor(deltatime);
	setCurDelay(Math::Max(getCurDelay() - deltatime, 0.0f));

	if (!getTarget().expired())
	{
		if (getCurDelay() == 0.0f)
		{
			attack();
		}

		attackMotion();
		auto muzzleVec = getPosition();
		muzzleVec.y += 100;
		auto toVec = getTarget().lock()->getPosition() - muzzleVec;
		toVec.Normalize();
		rotateToNewForward(toVec);
	}
}

void Blaster::actorInput()
{

}

void Blaster::attack()
{
	auto target = getTarget().lock();

	auto arrow = std::make_shared<Arrow>(getScene());
	arrow->setScale(getScale());

	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.Normalize();
	arrow->rotateToNewForward(toVec);

	arrow->setPosition(getPosition());
	arrow->initailize();

	setCurDelay(getAttackDelay());
}

void Blaster::attackMotion()
{
	//auto half = getAttackDelay() / 10;

	//if (getCurDelay() > half)
	//{
	//	setPosition(getPosition() - getForward() * (2.0f - getCurDelay()) * 10.0f);
	//}
	//else
	//{
	//	setPosition(getPosition() - getForward() * getCurDelay() * 90.0f);
	//}
}