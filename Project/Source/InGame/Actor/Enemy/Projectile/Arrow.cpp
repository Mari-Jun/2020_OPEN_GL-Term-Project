#include "Arrow.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Component/BoxComponent.h"
#include "../../../../Game/Game.h"
#include "../../Player/MovePlayer.h"

Arrow::Arrow(const std::weak_ptr<class Scene>& scene)
	: Projectile(scene, PjtType::Arrow)
	, mLine(Vector3::Zero, Vector3::Zero)
{

}

Arrow::~Arrow()
{
	
}

void Arrow::initailize()
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

	//set collide line
	mLine.mStart = box.mMin;
	mLine.mEnd = box.mMax;
}

void Arrow::updateActor(float deltatime)
{
	float forwardSpeed = 800.0f;

	mMoveComponent->setForwardSpeed(forwardSpeed);

	
	collide();

	if (getPosition().y <= -30.0f)
	{
		setState(State::Dead);
	}
}

void Arrow::actorInput()
{

}

void Arrow::collide()
{
	updateWorldTransform();

	//localLine to worldLine
	Matrix4 worldTransform;
	convertWorldTransform(worldTransform);
	
	auto worldLine = LineSegment
	(
		Vector3::Transform(mLine.mStart, worldTransform),
		Vector3::Transform(mLine.mEnd, worldTransform)
	);

	const auto& allBoxes = getGame().lock()->getPhysEngine()->getBoxes();
	const auto& boxes = allBoxes.find(Actor::getTypeToString(Actor::Type::Player));
	if (boxes != allBoxes.end())
	{
		for (const auto& b : boxes->second)
		{
			if (Intersect(worldLine, b.lock()->getWorldBox()))
			{
				auto owner = std::dynamic_pointer_cast<MovePlayer>(b.lock()->getOwner().lock());
				owner->decreaseHp(5.0f);
				setState(State::Dead);
				return;
			}
		}
	}
}