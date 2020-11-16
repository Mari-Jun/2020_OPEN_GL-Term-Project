#include "Bow.h"
#include "../Projectile/Arrow.h"
#include "../../../../Game/Game.h"

Bow::Bow(const std::weak_ptr<class Scene>& scene)
	: EnemyTower(scene, EnemyTower::Type::Ballista_Bow)
	, mAttackDelay(1.0f)
	, mCurDelay(mAttackDelay)
{

}

Bow::~Bow()
{

}

void Bow::initailize()
{
	EnemyTower::initailize();
}

void Bow::updateActor(float deltatime)
{
	EnemyTower::updateActor(deltatime);
	mCurDelay = Math::Max(mCurDelay - deltatime, 0.0f);

	if (!getTarget().expired())
	{
		if (mCurDelay == 0.0f)
		{
			attack();
		}

		attackMotion();
		
		/*auto a = getTarget().lock()->getPosition() - getPosition();
		auto b = getForward();
		a.Normalize();

		auto rad = Vector3::Dot(a, b);
		rad = Math::Clamp(rad, -1.0f, 1.0f);
		auto angle = Math::Acos(rad);

		float speed = 0.0f;

		if (!Math::NearZero(rad))
		{
			std::cout << angle << std::endl;
			setRotation(Quaternion::Concatenate(getRotation(), Quaternion(getSide(), angle)));
		}*/
	}
}

void Bow::actorInput()
{

}

void Bow::attack()
{
	auto target = getTarget().lock();

	auto arrow = std::make_shared<Arrow>(getScene());
	arrow->setScale(getScale());

	auto toVec = getTarget().lock()->getPosition() - getPosition();
	toVec.Normalize();
	float angle = Math::Acos(Vector3::Dot(Vector3::UnitZ, toVec));
	auto side = Vector3::Cross(Vector3::UnitZ, toVec);
	side.Normalize();
	arrow->setRotation(Quaternion(side, angle));
	arrow->setPosition(getPosition());
	arrow->initailize();

	mCurDelay = mAttackDelay;
}

void Bow::attackMotion()
{
	auto half = mAttackDelay / 10;

	if (mCurDelay > half)
	{
		setPosition(getPosition() - getForward() * (2.0f - mCurDelay) * 10.0f);
	}
	else
	{
		setPosition(getPosition() - getForward() * mCurDelay * 90.0f);
	}
}