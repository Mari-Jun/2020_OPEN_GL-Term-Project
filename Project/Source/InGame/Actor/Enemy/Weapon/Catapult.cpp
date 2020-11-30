#include "Catapult.h"
#include "../Projectile/Rock.h"
#include "../../../Scene/GameScene.h"
#include "../../../Scene/EditScene.h"
#include "../../../../Game/Game.h"

#include "../../../../Game/Sound/Sound.h"
Catapult::Catapult(const std::weak_ptr<class Scene>& scene)
	: Weapon(scene)
{
	setAttackDelay(3.0f);
}

Catapult::~Catapult()
{
	mRock->setState(State::Dead);
}

void Catapult::initailize()
{
	Weapon::initailize();
	initRock();
}

void Catapult::setEffectIndex(int index)
{
	mEffectindex = index;
}

void Catapult::initRock()
{
	mRock = std::make_shared<Rock>(getScene());

	mRockScaleTime = 1;
	auto objectOwner = std::dynamic_pointer_cast<GameScene>(getScene().lock());

	if (objectOwner.use_count())
	{		
		mRock->setPosition(getPosition() - Vector3(0.0f, -40.0f, 80.0f));	//초기 방향은 z방향을 쳐다보고잇으니 처음생성할땐 10만큼 뒤로 가줌
	}else{
		mRock->setPosition(getPosition() - Vector3(0.0f, -5.0f, 10.0f));	//초기 방향은 z방향을 쳐다보고잇으니 처음생성할땐 10만큼 뒤로 가줌
	}

	mRock->setScale(getScale());
	mRock->setforwardSpeed(0.0f);
	mRock->setupSpeed(0.0f);
	mRock->initailize();
	mRock->setEffectIndex(1);	//맨첨에 생기는거라 mEffect가 설정이 안 된 상태임
	mRock->setScale(0.01f);
}

void Catapult::initRock(Vector3 toVec)
{
	mRock = std::make_shared<Rock>(getScene());

	mRockScaleTime = 1;
	//auto toVec = getTarget().lock()->getPosition() - getPosition();
	Vector3 toVectmp = toVec;
	toVectmp.Normalize();
	toVectmp.y = -0.5f;
	mRock->setPosition(getPosition() - (toVectmp * 80));

	mRock->setScale(getScale());
	mRock->setforwardSpeed(0.0f);
	mRock->setupSpeed(0.0f);
	mRock->initailize();
	mRock->setScale(0.01f);
	mRock->setEffectIndex(mEffectindex);
	toVec.y = 0.0f;
	toVec.Normalize();
	rotateToNewForward(toVec);
}


void Catapult::updateActor(float deltatime)
{
	Weapon::updateActor(deltatime);
	setCurDelay(Math::Max(getCurDelay() - deltatime, 0.0f));

	
	if (!getTarget().expired())
	{
		if (getCurDelay() == 0.0f)
		{
			auto Sound = getGame().lock()->getSound();
			auto distVec = Sound->getListener() - getPosition();
			Sound->playDist(static_cast<int>(Sound::effectName::catapult), mEffectindex, distVec.Length());
			attack();
		}

		attackMotion();

	}

	//커지는거 100번 반복
	if (mRockScaleTime < 100.0f)
	{
		mRockScaleTime += 1.0f;
		mRock->setScale(1.03f);
	}
}

void Catapult::actorInput()
{

}

void Catapult::attack()
{

	fire();
	
	setCurDelay(getAttackDelay());
}

void Catapult::fire()
{
	//여기에 발사된거를 스피드를 주고
	mRock->setflag(true);
	float Distxz = 0.0f;

	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.y = 0.0f;
	Distxz = toVec.Length();

	toVec.Normalize();
	mRock->rotateToNewForward(toVec);

	//1.5초가 돌에서 플레이어까지 걸리는 시간 , y도 그렇게 구해줘야하는데 자유낙하방정식으로 들어가버려서 그냥 대충
	//상수 넣으면서 계산했음 
	mRock->setforwardSpeed(Distxz / 1.5f);
	mRock->setupSpeed(350);


	//다시 생성해서 캐터펄트가 관리를 하지 못하게 함  사실 이 fire 구문 자체가 타겟이 있을때만 들어오는거라 무조건 타겟이 있긴함
	// 아래 else문은 지워줘도 무방
	if (!getTarget().expired())
	{
		//타겟이 정해져있다면 타겟기준으로 생성
		initRock(getTarget().lock()->getPosition() - getPosition());
	}
	else {
		//아니라면 일반 생성
		initRock();
	}
}

void Catapult::attackMotion()
{
	auto AttackDelay_10percent = getAttackDelay() / 10;
	// 

	//발사동작
	if (getCurDelay() > getAttackDelay() - AttackDelay_10percent * 1.5f)
	{
		auto toVec = getTarget().lock()->getPosition() - getPosition();
		toVec.y = 0.0f;
		toVec.y -= moveY;
		toVec.Normalize();
		rotateToNewForward(toVec);
		if (moveY < 805)
		{
			moveY += 10.0f;
		}
	}
	else//장전동작
	{
		auto toVec = getTarget().lock()->getPosition() - getPosition();
		auto toRockVec = toVec;
		toVec.y = 0.0f;
		toVec.y -= moveY;
		toVec.Normalize();

		rotateToNewForward(toVec);

		toRockVec.Normalize();
		toRockVec.y = -0.5f;
		mRock->setPosition(getPosition() - (toRockVec * 80));
		mRock->rotateToNewForward(toRockVec);

		if(moveY - 5 >0)
			moveY -= 5;
	}
}
