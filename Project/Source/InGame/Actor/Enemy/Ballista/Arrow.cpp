#include "Arrow.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Game.h"

Arrow::Arrow(const std::weak_ptr<class Scene>& scene)
	: Actor(scene)
{

}

Arrow::~Arrow()
{
	
}

void Arrow::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Enemy/Arrow"));
	mMeshComponent->initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void Arrow::updateActor(float deltatime)
{
	float forwardSpeed = 800.0f;

	mMoveComponent->setForwardSpeed(forwardSpeed);

	if (getPosition().y <= -30.0f)
	{
		setState(State::Dead);
	}
}

void Arrow::actorInput()
{

}