#include "Blaster.h"
#include "../Projectile/Arrow.h"
#include "../Projectile/Laser.h"
#include "../../../../Game/Game.h"

Blaster::Blaster(const std::weak_ptr<class Scene>& scene)
	: Weapon(scene)
{

	setAttackDelay(1.0f);
}

Blaster::~Blaster()
{

}

void Blaster::initailize()
{
	Weapon::initailize();
	initLaser();
}

void Blaster::initLaser()
{
	
	mLaser = std::make_shared<Laser>(getScene());
	mLaser->setScale(getScale() * 0.01);
	mLaser->setScale(Vector3(1, 1, 1));

	//auto toVec = getTarget().lock()->getPosition() - getPosition();
	//toVec.Normalize();
	//mLaser->rotateToNewForward(toVec);

	mLaser->setPosition(getPosition());
	mLaser->initailize();
}

void Blaster::updateActor(float deltatime)
{
	Weapon::updateActor(deltatime);
	setCurDelay(Math::Max(getCurDelay() - deltatime, 0.0f));

	if (!getTarget().expired())
	{
		if (getCurDelay() == 0.0f)
		{
			target_invalid = true;

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

	//auto target = getTarget().lock();
	//if (target_invalid == true)
	//{
	//	auto laser = std::make_shared<Laser>(getScene());
	//	laser->setScale(getScale() * 0.01);

	//	auto toVec = getTarget().lock()->getPosition() - getPosition();
	//	toVec.Normalize();
	//	laser->rotateToNewForward(toVec);

	//	laser->setPosition(getPosition());
	//	laser->initailize();
	//}



	setCurDelay(getAttackDelay());
}

void Blaster::attackMotion()
{
	auto AttackDelay_10percent = getAttackDelay() / 10;
	// 

	//발사동작
	if (getCurDelay() > getAttackDelay() - AttackDelay_10percent * 3.0f)
	{
		std::cout << getCurDelay();
		auto muzzleVec = getPosition();
		muzzleVec.y += 100;
		auto toVec = getTarget().lock()->getPosition() - muzzleVec;
		auto Scala = toVec;
		auto RealScala = Scala.Length();
		std::cout << RealScala << "\n";
		toVec.y += 20;
		toVec.Normalize();
		mLaser->rotateToNewForward(toVec);
		Scala = Scala / 2.0f;
		mLaser->setScale(Vector3(3.0 * getCurDelay(), 3.0 * getCurDelay(), RealScala / 62 ));
		mLaser->setPosition(Scala + muzzleVec);
	}
	else
	{
		mLaser->setScale(0.0f);
	}

	
}