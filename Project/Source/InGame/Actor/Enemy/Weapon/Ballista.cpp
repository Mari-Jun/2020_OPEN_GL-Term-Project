#include "Ballista.h"
#include "../Projectile/Arrow.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Sound/Sound.h"

Ballista::Ballista(const std::weak_ptr<class Scene>& scene)
	: Weapon(scene)
{

}

Ballista::~Ballista()
{

}

void Ballista::initailize()
{
	Weapon::initailize();
}

void Ballista::updateActor(float deltatime)
{
	Weapon::updateActor(deltatime);
	setCurDelay(Math::Max(getCurDelay() - deltatime, 0.0f));

	if (!getTarget().expired())
	{
		if (getCurDelay() == 0.0f)
		{
			
			getGame().lock()->getSound()->play(static_cast<int>(Sound::CHANNEL::effect), static_cast<int>(Sound::effectName::Arrow1));
			
			attack();
		}

		attackMotion();

		auto toVec = getTarget().lock()->getPosition() - getPosition();
		toVec.Normalize();
		rotateToNewForward(toVec);
	}
}

void Ballista::actorInput()
{

}

void Ballista::attack()
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

void Ballista::attackMotion()
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