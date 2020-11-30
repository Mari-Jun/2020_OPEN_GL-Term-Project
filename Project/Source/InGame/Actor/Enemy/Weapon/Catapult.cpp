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
		mRock->setPosition(getPosition() - Vector3(0.0f, -40.0f, 80.0f));	//�ʱ� ������ z������ �Ĵٺ��������� ó�������Ҷ� 10��ŭ �ڷ� ����
	}else{
		mRock->setPosition(getPosition() - Vector3(0.0f, -5.0f, 10.0f));	//�ʱ� ������ z������ �Ĵٺ��������� ó�������Ҷ� 10��ŭ �ڷ� ����
	}

	mRock->setScale(getScale());
	mRock->setforwardSpeed(0.0f);
	mRock->setupSpeed(0.0f);
	mRock->initailize();
	mRock->setEffectIndex(1);	//��÷�� ����°Ŷ� mEffect�� ������ �� �� ������
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

	//Ŀ���°� 100�� �ݺ�
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
	//���⿡ �߻�ȰŸ� ���ǵ带 �ְ�
	mRock->setflag(true);
	float Distxz = 0.0f;

	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.y = 0.0f;
	Distxz = toVec.Length();

	toVec.Normalize();
	mRock->rotateToNewForward(toVec);

	//1.5�ʰ� ������ �÷��̾���� �ɸ��� �ð� , y�� �׷��� ��������ϴµ� �������Ϲ��������� �������� �׳� ����
	//��� �����鼭 ������� 
	mRock->setforwardSpeed(Distxz / 1.5f);
	mRock->setupSpeed(350);


	//�ٽ� �����ؼ� ĳ����Ʈ�� ������ ���� ���ϰ� ��  ��� �� fire ���� ��ü�� Ÿ���� �������� �����°Ŷ� ������ Ÿ���� �ֱ���
	// �Ʒ� else���� �����൵ ����
	if (!getTarget().expired())
	{
		//Ÿ���� �������ִٸ� Ÿ�ٱ������� ����
		initRock(getTarget().lock()->getPosition() - getPosition());
	}
	else {
		//�ƴ϶�� �Ϲ� ����
		initRock();
	}
}

void Catapult::attackMotion()
{
	auto AttackDelay_10percent = getAttackDelay() / 10;
	// 

	//�߻絿��
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
	else//��������
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
