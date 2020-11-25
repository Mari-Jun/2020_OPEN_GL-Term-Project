#include "Cannon.h"
#include "../Projectile/CannonBall.h"
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
	Weapon::updateActor(deltatime);
	setCurDelay(Math::Max(getCurDelay() - deltatime, 0.0f));

	if (!getTarget().expired())
	{
		if (getCurDelay() == 0.0f)
		{
			attack();
		}

		attackMotion();

		auto toVec = getTarget().lock()->getPosition() - getPosition();
		toVec.Normalize();
		rotateToNewForward(toVec);
	}
}

void Cannon::actorInput()
{

}

void Cannon::attack()
{
	auto target = getTarget().lock();

	auto rock = std::make_shared<CannonBall>(getScene());
	rock->setScale(getScale()*0.09);

	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.Normalize();
	rock->rotateToNewForward(toVec);

	rock->setPosition(getPosition());
	rock->initailize();

	setCurDelay(getAttackDelay());
}

void Cannon::attackMotion()
{
	auto half = getAttackDelay() / 10;

	if (getCurDelay() > half)
	{
		setPosition(getPosition() - getForward() * (2.0f - getCurDelay()) * 10.0f);
	}
	else
	{
		setPosition(getPosition() - getForward() * getCurDelay() * 90.0f);
	}
}