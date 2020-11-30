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

	//일반 포지션
	auto muzzleVec = getPosition();

	//일반포지션에서 아군까지의 벡터 기계기준 z축 벡터임 
	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.Normalize();

	// 그 벡터와 y 축벡터를 외적함으로 기계기준 x축 벡터 획득 
	auto xVec = Vector3::Cross(toVec, Vector3::UnitY);
	//그 기계의 좌우벡터와 가리키는벡터를 외적함으로 기계의 UP벡터 즉 y축 벡터 획득
	auto forwarding = Vector3::Cross(xVec, toVec);
	forwarding.Normalize();
	//기본 포지션에서 기계의 y축벡터 100만큼 이동  
	muzzleVec += forwarding * 100;

	//포지션 하나 더 얻어와서 기계가 돌아가는데 쓰이는 벡터 구함 실제로 쓰이는 기계의 z축벡터는 y += 100 인 상태에서 하는것이기때문에 다시 써주는것
	auto pre = getPosition();
	pre.y += 100;
	//toVec를 재활용해서, 그 벡터 구함 z축 벡터 
	toVec = getTarget().lock()->getPosition() - pre;
	toVec.Normalize();
	//그래서 155만큼 앞으로 와주고 28만큼 왼쪽으로 가주면 이게 오른쪽 구멍에서 나오는 레이저벡터의 위치벡터
	muzzleVec += toVec * 155;
	muzzleVec -= xVec * 28;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//그래서 레이저벡터의 위치벡터에서부터 다시 플레이어까지 방향벡터를 구함 그리고 그 스칼라값은 길이 이므로 저장
	auto LaserVec = getTarget().lock()->getPosition() - muzzleVec;
	auto Scala = LaserVec.Length();
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//toVec 다시 재활용 해서 방향벡터의 정규화를 시켜서 그걸로 레이저의 위치를 구함 
	toVec = getTarget().lock()->getPosition() - muzzleVec;
	toVec.Normalize();
	mLaser->rotateToNewForward(toVec);


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	// 레이저를 앞으로 땡기는 작업 
	// LaserVec을 2로 나누면 크기가 반토막인 벡터가 됨 . 이걸 최종적으로 레이저쏘는 입구에서 더해줘서 반 앞으로 전진할것
	LaserVec = LaserVec / 2.0f;
	auto time_delay = 1 - getCurDelay();

	time_delay *= to_delay;
	//time_delay로 인해서 크기는 점점 줄고, Scala에 적절한 값을 나눠서 길이 또한 정해줌
	mLaser->setScale(Vector3(1.3 * (1.0 - time_delay), 1.3 * (1.0 - time_delay), Scala / 60));
	mLaser->setPosition(LaserVec + muzzleVec);

}
void Blaster::rightLaser()
{
	float to_delay = 3.0f;

	//일반 포지션
	auto muzzleVec = getPosition();

	//일반포지션에서 아군까지의 벡터 기계기준 z축 벡터임 
	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.Normalize();

	// 그 벡터와 y 축벡터를 외적함으로 기계기준 x축 벡터 획득 
	auto xVec = Vector3::Cross(toVec, Vector3::UnitY);
	//그 기계의 좌우벡터와 가리키는벡터를 외적함으로 기계의 UP벡터 즉 y축 벡터 획득
	auto forwarding = Vector3::Cross(xVec, toVec);
	forwarding.Normalize();
	//기본 포지션에서 기계의 y축벡터 100만큼 이동  
	muzzleVec += forwarding * 100;

	//포지션 하나 더 얻어와서 기계가 돌아가는데 쓰이는 벡터 구함 실제로 쓰이는 기계의 z축벡터는 y += 100 인 상태에서 하는것이기때문에 다시 써주는것
	auto pre = getPosition();
	pre.y += 100;
	//toVec를 재활용해서, 그 벡터 구함 z축 벡터 
	toVec = getTarget().lock()->getPosition() - pre;
	toVec.Normalize();
	//그래서 155만큼 앞으로 와주고 28만큼 오른쪽으로 가주면 이게 오른쪽 구멍에서 나오는 레이저벡터의 위치벡터
	muzzleVec += toVec * 155;
	muzzleVec += xVec * 28;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//그래서 레이저벡터의 위치벡터에서부터 다시 플레이어까지 방향벡터를 구함 그리고 그 스칼라값은 길이 이므로 저장
	auto LaserVec = getTarget().lock()->getPosition() - muzzleVec;
	auto Scala = LaserVec.Length();
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//toVec 다시 재활용 해서 방향벡터의 정규화를 시켜서 그걸로 레이저의 위치를 구함 
	toVec = getTarget().lock()->getPosition() - muzzleVec;
	toVec.Normalize();
	mRaser->rotateToNewForward(toVec);


	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	// 레이저를 앞으로 땡기는 작업 
	// LaserVec을 2로 나누면 크기가 반토막인 벡터가 됨 . 이걸 최종적으로 레이저쏘는 입구에서 더해줘서 반 앞으로 전진할것
	LaserVec = LaserVec / 2.0f;
	auto time_delay = 1 - getCurDelay();

	time_delay *= to_delay;
	//time_delay로 인해서 크기는 점점 줄고, Scala에 적절한 값을 나눠서 길이 또한 정해줌
	mRaser->setScale(Vector3(1.3 * (1.0 - time_delay), 1.3 * (1.0 - time_delay), Scala / 60));
	mRaser->setPosition(LaserVec + muzzleVec);

}
void Blaster::attackMotion()
{
	auto AttackDelay_10percent = getAttackDelay() / 10;
	// 
	float to_delay = 3.0f;	// 어택딜레이에 곱해줄 수 
	//발사동작
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