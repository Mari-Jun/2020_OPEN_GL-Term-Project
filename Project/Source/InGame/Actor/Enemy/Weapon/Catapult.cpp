#include "Catapult.h"
#include "../Projectile/Rock.h"
#include "../../../../Game/Game.h"

Catapult::Catapult(const std::weak_ptr<class Scene>& scene)
	: Weapon(scene)
{
	setAttackDelay(3.0f);
	forVec = Vector3(0, 0, 0);
}

Catapult::~Catapult()
{

}

void Catapult::initailize()
{
	Weapon::initailize();
	initRock();
	
}

void Catapult::initRock()
{
	mRock = std::make_shared<Rock>(getScene());


	//auto toVec = getTarget().lock()->getPosition() - getPosition();
	//toVec.Normalize();
	//toVec.y = -0.5;
	//mRock->setPosition(getPosition() - (toVec * 80));
	mRock->setPosition(getPosition());

	//mRock->rotateToNewForward(toVec);

	mRock->setScale(getScale());
	mRock->setforwardSpeed(0);
	mRock->setupSpeed(0);
	mRock->initailize();
	mRock->setScale(0.1);
}

void Catapult::initRock(Vector3 toVec)
{
	mRock = std::make_shared<Rock>(getScene());


	//auto toVec = getTarget().lock()->getPosition() - getPosition();
	Vector3 toVectmp = toVec;
	toVectmp.Normalize();
	toVectmp.y = -0.5;
	mRock->setPosition(getPosition() - (toVectmp * 80));
	//mRock->setPosition(getPosition());

	//mRock->rotateToNewForward(toVec);

	mRock->setScale(getScale());
	mRock->setforwardSpeed(0);
	mRock->setupSpeed(0);
	mRock->initailize();
	mRock->setScale(0.1);
	toVec.y = 0;
	toVec.Normalize();
	rotateToNewForward(toVec);
}

void Catapult::resetRock()
{
	mRock.reset();
}

void Catapult::updateActor(float deltatime)
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

		


	}
}

void Catapult::actorInput()
{

}

void Catapult::attack()
{
	auto target = getTarget().lock();

	fire();
	
	setCurDelay(getAttackDelay());
}

void Catapult::fire()
{
	//여기에 발사된거를 스피드를 주고
	mRock->setflag(true);
	float Distxz = 0.0f;
	float Disty = 0.0f;
	if (!getTarget().expired())
	{
		auto toVec = getTarget().lock()->getPosition() - getPosition();
		toVec.x = 0;
		toVec.z = 0;
		Disty = toVec.Length();

		toVec = getTarget().lock()->getPosition() - getPosition();
		toVec.y = 0.0f;
		forVec = toVec;
		Distxz = toVec.Length();



		toVec.Normalize();
		mRock->rotateToNewForward(toVec);

	}
	mRock->setforwardSpeed(Distxz / 1.5f);
	mRock->setupSpeed(250);


	//다시 생성해서 캐터펄트가 관리를 하지 못하게 함 
	if (!getTarget().expired())
	{
		initRock(getTarget().lock()->getPosition() - getPosition());
	}
	else {
		initRock();
	}
}

void Catapult::attackMotion()
{
	auto half = getAttackDelay() / 2;
	//3초인데 10으로 ㄹ나누면 1.5초


	if (getCurDelay() > 2.5)
	{
		auto toVec = Vector3(forVec.x - moveX, forVec.y - moveY, forVec.z - moveY);
		toVec.Normalize();
		rotateToNewForward(toVec);
		if (moveY < 805)
		{
			moveY += 10.0f;
			//moveX -= 20.0f;
		}
		/*if (forVec.x * forVec.z < 0)
		{
			if (moveY < 805)
				moveY += 20.0f;
		}
		else {

		}*/
		//setPosition(getPosition() - getForward() * (2.0f - getCurDelay()) * 10.0f);
	}
	else
	{

		auto toVec = getTarget().lock()->getPosition() - getPosition();
		auto toVectmp = toVec;
		toVec.y = 0.0f;
		toVec.y -= moveY;
		toVec.Normalize();

		rotateToNewForward(toVec);

		toVectmp.Normalize();
		toVectmp.y = -0.5;
		mRock->setPosition(getPosition() - (toVectmp * 80));
		mRock->rotateToNewForward(toVectmp);


		/*auto toVec = Vector3(forVec.x, forVec.y - moveY, forVec.z);
		toVec.Normalize();
		rotateToNewForward(toVec);*/
		/*if (moveY > 0)
			moveY += -8.0f;*/
		if(moveY - 5 >0)
			moveY -= 5;
		moveX = 0;
		moveZ = 0;
		//setPosition(getPosition() - getForward() * getCurDelay() * 90.0f);
	}
}

void Catapult::reload()
{
	
}