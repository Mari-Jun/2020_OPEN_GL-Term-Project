#include "Blaster.h"
#include "../../../../Game/Math/Math.h"

#include "../Projectile/Arrow.h"
#include "../Projectile/Laser.h"
#include "../../../../Game/Game.h"

#include "../../../../Game/Sound/Sound.h"

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

void Blaster::setEffectIndex(int index)
{
	mEffectindex = index;
}

void Blaster::initLaser()
{

	mLaser = std::make_shared<Laser>(getScene());
	mLaser->setScale(getScale() * 0.01);
	mLaser->setScale(Vector3(1, 1, 1));
	mLaser->setPosition(getPosition());
	mLaser->initailize();


	mRaser = std::make_shared<Laser>(getScene());
	mRaser->setScale(getScale() * 0.01);
	mRaser->setScale(Vector3(1, 1, 1));
	mRaser->setPosition(getPosition());
	mRaser->initailize();

}

void Blaster::disappear()
{

	mLaser->setScale(0.0f);
	mRaser->setScale(0.0f);
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

			auto Sound = getGame().lock()->getSound();
			auto distVec = Sound->getListener() - getPosition();
			Sound->playDist(static_cast<int>(Sound::effectName::laser), mEffectindex, distVec.Length());

			attack();
		}
		attackMotion();

		auto muzzleVec = getPosition();
		muzzleVec.y += 100;
		auto toVec = getTarget().lock()->getPosition() - muzzleVec;
		toVec.Normalize();
		rotateToNewForward(toVec);
	}
	else {
		disappear();
	}
}

void Blaster::actorInput()
{

}

void Blaster::attack()
{

	setCurDelay(getAttackDelay());
}



void Blaster::leftLaser()
{
	float to_delay = 3.0f;

	//�Ϲ� ������
	auto muzzleVec = getPosition();

	//�Ϲ������ǿ��� �Ʊ������� ���� ������ z�� ������ 
	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.Normalize();

	// �� ���Ϳ� y �຤�͸� ���������� ������ x�� ���� ȹ�� 
	auto xVec = Vector3::Cross(toVec, Vector3::UnitY);
	//�� ����� �¿캤�Ϳ� ����Ű�º��͸� ���������� ����� UP���� �� y�� ���� ȹ��
	auto forwarding = Vector3::Cross(xVec, toVec);
	forwarding.Normalize();
	//�⺻ �����ǿ��� ����� y�຤�� 100��ŭ �̵�  
	muzzleVec += forwarding * 100;

	//������ �ϳ� �� ���ͼ� ��谡 ���ư��µ� ���̴� ���� ���� ������ ���̴� ����� z�຤�ʹ� y += 100 �� ���¿��� �ϴ°��̱⶧���� �ٽ� ���ִ°�
	auto pre = getPosition();
	pre.y += 100;
	//toVec�� ��Ȱ���ؼ�, �� ���� ���� z�� ���� 
	toVec = getTarget().lock()->getPosition() - pre;
	toVec.Normalize();
	//�׷��� 155��ŭ ������ ���ְ� 28��ŭ �������� ���ָ� �̰� ������ ���ۿ��� ������ ������������ ��ġ����
	muzzleVec += toVec * 155;
	muzzleVec -= xVec * 28;

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//�׷��� ������������ ��ġ���Ϳ������� �ٽ� �÷��̾���� ���⺤�͸� ���� �׸��� �� ��Į���� ���� �̹Ƿ� ����
	auto LaserVec = getTarget().lock()->getPosition() - muzzleVec;
	auto Scala = LaserVec.Length();
	//�ѤѤѤѤѤѤѤѤѤѤѤ�
	//toVec �ٽ� ��Ȱ�� �ؼ� ���⺤���� ����ȭ�� ���Ѽ� �װɷ� �������� ��ġ�� ���� 
	toVec = getTarget().lock()->getPosition() - muzzleVec;
	toVec.Normalize();
	mLaser->rotateToNewForward(toVec);


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// �������� ������ ����� �۾� 
	// LaserVec�� 2�� ������ ũ�Ⱑ ���丷�� ���Ͱ� �� . �̰� ���������� ��������� �Ա����� �����༭ �� ������ �����Ұ�
	LaserVec = LaserVec / 2.0f;
	auto time_delay = 1 - getCurDelay();

	time_delay *= to_delay;
	//time_delay�� ���ؼ� ũ��� ���� �ٰ�, Scala�� ������ ���� ������ ���� ���� ������
	mLaser->setScale(Vector3(1.3 * (1.0 - time_delay), 1.3 * (1.0 - time_delay), Scala / 60));
	mLaser->setPosition(LaserVec + muzzleVec);

}
void Blaster::rightLaser()
{
	float to_delay = 3.0f;

	//�Ϲ� ������
	auto muzzleVec = getPosition();

	//�Ϲ������ǿ��� �Ʊ������� ���� ������ z�� ������ 
	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.Normalize();

	// �� ���Ϳ� y �຤�͸� ���������� ������ x�� ���� ȹ�� 
	auto xVec = Vector3::Cross(toVec, Vector3::UnitY);
	//�� ����� �¿캤�Ϳ� ����Ű�º��͸� ���������� ����� UP���� �� y�� ���� ȹ��
	auto forwarding = Vector3::Cross(xVec, toVec);
	forwarding.Normalize();
	//�⺻ �����ǿ��� ����� y�຤�� 100��ŭ �̵�  
	muzzleVec += forwarding * 100;

	//������ �ϳ� �� ���ͼ� ��谡 ���ư��µ� ���̴� ���� ���� ������ ���̴� ����� z�຤�ʹ� y += 100 �� ���¿��� �ϴ°��̱⶧���� �ٽ� ���ִ°�
	auto pre = getPosition();
	pre.y += 100;
	//toVec�� ��Ȱ���ؼ�, �� ���� ���� z�� ���� 
	toVec = getTarget().lock()->getPosition() - pre;
	toVec.Normalize();
	//�׷��� 155��ŭ ������ ���ְ� 28��ŭ ���������� ���ָ� �̰� ������ ���ۿ��� ������ ������������ ��ġ����
	muzzleVec += toVec * 155;
	muzzleVec += xVec * 28;

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//�׷��� ������������ ��ġ���Ϳ������� �ٽ� �÷��̾���� ���⺤�͸� ���� �׸��� �� ��Į���� ���� �̹Ƿ� ����
	auto LaserVec = getTarget().lock()->getPosition() - muzzleVec;
	auto Scala = LaserVec.Length();
	//�ѤѤѤѤѤѤѤѤѤѤѤ�
	//toVec �ٽ� ��Ȱ�� �ؼ� ���⺤���� ����ȭ�� ���Ѽ� �װɷ� �������� ��ġ�� ���� 
	toVec = getTarget().lock()->getPosition() - muzzleVec;
	toVec.Normalize();
	mRaser->rotateToNewForward(toVec);


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// �������� ������ ����� �۾� 
	// LaserVec�� 2�� ������ ũ�Ⱑ ���丷�� ���Ͱ� �� . �̰� ���������� ��������� �Ա����� �����༭ �� ������ �����Ұ�
	LaserVec = LaserVec / 2.0f;
	auto time_delay = 1 - getCurDelay();

	time_delay *= to_delay;
	//time_delay�� ���ؼ� ũ��� ���� �ٰ�, Scala�� ������ ���� ������ ���� ���� ������
	mRaser->setScale(Vector3(1.3 * (1.0 - time_delay), 1.3 * (1.0 - time_delay), Scala / 60));
	mRaser->setPosition(LaserVec + muzzleVec);

}
void Blaster::attackMotion()
{
	auto AttackDelay_10percent = getAttackDelay() / 10;
	// 
	float to_delay = 3.0f;	// ���õ����̿� ������ �� 
	//�߻絿��
	if (getCurDelay() > getAttackDelay() - AttackDelay_10percent * to_delay)
	{
		leftLaser();
		rightLaser();

	}
	else
	{
		mLaser->setScale(0.0f);
		mRaser->setScale(0.0f);
	}


}