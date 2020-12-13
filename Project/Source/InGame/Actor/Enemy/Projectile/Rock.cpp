#include "Rock.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Component/BoxComponent.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Sound/Sound.h"

#include "../../Player/MovePlayer.h"
#include "../Weapon/Catapult.h"

#include <random>

Rock::Rock(const std::weak_ptr<class Scene>& scene)
	: Projectile(scene, PjtType::Rock)
	, mSphere(Vector3::Zero,0)
{
	
}

Rock::~Rock()
{

}

void Rock::initailize()
{
	Projectile::initailize();

	//Create MeshComponent
	auto mesh = loadMesh();
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	const auto& box = mesh->getBox();

	//set collide Sphere
	mSphere.mCenter = (box.mMin + box.mMax) / 2.0f;

	Vector3 Vec(box.mMax - box.mMin);
	Vec.y = 0;
	mSphere.mRadius = Vec.Length() / 2.0f;
}

void Rock::gravity(float deltatime)
{
	upSpeed -= 10;
}

void Rock::updateActor(float deltatime)
{
	if (flag == true)
	{
		mMoveComponent->setForwardSpeed(forwardSpeed);
		mMoveComponent->setUpSpeed(upSpeed);
		gravity(deltatime);

	}
	collide();

	if (getPosition().y <= 10.0f)
	{
		setState(State::Dead);

		if (split == false)
		{
			auto Sound = getGame().lock()->getSound();
			auto distVec = Sound->getListener() - getPosition();
			Sound->playDist(static_cast<int>(Sound::effectName::rockbroken), mEffectindex, distVec.Length());

			for (int i = 0; i < 12; ++i)	//i의 갯수는 파편의 개수
			{
				makeSplitRock();
			}
		}

	}
}

void Rock::actorInput()
{

}

void Rock::collide()
{
	updateWorldTransform();

	//localSphere to worldSphere
	Matrix4 worldTransform;
	convertWorldTransform(worldTransform);

	auto worldSphere = Sphere
	(
		Vector3::Transform(mSphere.mCenter, worldTransform),
		mSphere.mRadius * getScale().x
	);

	const auto& allBoxes = getGame().lock()->getPhysEngine()->getBoxes();
	const auto& boxes = allBoxes.find(Actor::getTypeToString(Actor::Type::Player));
	if (boxes != allBoxes.end())
	{
		for (const auto& b : boxes->second)
		{
			if (Intersect(worldSphere, b.lock()->getWorldBox()))
			{
				if (split == false)
				{
					auto Sound = getGame().lock()->getSound();
					auto distVec = Sound->getListener() - getPosition();
					Sound->playDist(static_cast<int>(Sound::effectName::rockbroken), mEffectindex, distVec.Length());
					for (int i = 0; i < 12; ++i)	//i의 갯수는 파편의 개수
					{
						makeSplitRock();
					}
				}
				auto owner = std::dynamic_pointer_cast<MovePlayer>(b.lock()->getOwner().lock());
				owner->decreaseHp(5.0f);
				setState(State::Dead);

				return;
			}
		}
	}
}


void Rock::makeSplitRock()
{
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<int> Rxz(-100, 100);
	std::uniform_int_distribution<int> RSpeed(50, 100);
	std::uniform_int_distribution<int> RUpSpeed(200, 350);

	auto rock = std::make_shared<Rock>(getScene());
	rock->setScale(getScale() * 0.3f);

	auto toVec = Vector3(static_cast<float>(Rxz(mersenne)), 0.0f, static_cast<float>(Rxz(mersenne)));
	toVec.Normalize();
	rock->rotateToNewForward(toVec);

	rock->setforwardSpeed(static_cast<float>(RSpeed(mersenne)));
	rock->setupSpeed(static_cast<float>(RUpSpeed(mersenne)));
	rock->setPosition(getPosition() + Vector3(0, 20, 0));
	rock->initailize();
	rock->setflag(1);
	rock->split = true;
}