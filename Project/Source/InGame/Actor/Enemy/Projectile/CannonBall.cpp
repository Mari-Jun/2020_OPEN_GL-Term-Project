#include "CannonBall.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Component/BoxComponent.h"
#include "../../../../Game/Game.h"
#include "../../Player/MovePlayer.h"



CannonBall::CannonBall(const std::weak_ptr<class Scene>& scene)
	: Projectile(scene, PjtType::CannonBall)
	, mSphere(Vector3::Zero, 0)
{

}

CannonBall::~CannonBall()
{

}

void CannonBall::initailize()
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

void CannonBall::updateActor(float deltatime)
{
	float forwardSpeed = 800.0f;

	mMoveComponent->setForwardSpeed(forwardSpeed);

	collide();

	if (getPosition().y <= -30.0f)
	{
		setState(State::Dead);
	}
}

void CannonBall::actorInput()
{

}

void CannonBall::collide()
{
	updateWorldTransform();

	//localLine to worldLine
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
				auto owner = std::dynamic_pointer_cast<MovePlayer>(b.lock()->getOwner().lock());
				owner->decreaseHp(5.0f);
				setState(State::Dead);

				return;
			}
		}
	}
}