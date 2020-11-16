#include "Arrow.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Component/BoxComponent.h"
#include "../../../../Game/Game.h"

Arrow::Arrow(const std::weak_ptr<class Scene>& scene)
	: Projectile(scene, Type::Arrow)
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

	auto worldTransform = Matrix4::CreateScale(getScale());
	worldTransform *= Matrix4::CreateFromQuaternion(getRotation());
	worldTransform *= Matrix4::CreateTranslation(getPosition());

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
				setState(State::Dead);
				return;
			}
		}
	}
}