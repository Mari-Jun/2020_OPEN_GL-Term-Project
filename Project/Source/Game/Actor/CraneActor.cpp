#include "CraneActor.h"
#include "../Graphics/Window.h"
#include "../Game.h"
#include "../Component/MoveComponent.h"
#include "../Graphics/Mesh/MeshComponent.h"
#include "../Input/KeyBoard.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Renderer/Renderer.h"
#include "CMiddleActor.h"

CraneActor::CraneActor(const std::weak_ptr<class Game>& game)
	: Actor(game)
{
	std::cerr << "Create CraneActor\n";
}

CraneActor::~CraneActor()
{
	std::cerr << "Destory CraneActor\n";
}

void CraneActor::initailize()
{
	Actor::initailize();
	
	setScale(Vector3(16.0f, 2.0f, 16.0f));

	//Create MeshComponent
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer()->shared_from_this());
	mMeshComponent->initailize();
	mMeshComponent->setMesh(getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Box.obj"));
	mMeshComponent->setColor(Vector3(0.0f, 1.0f, 1.0f));

	//Create MoveComponenet
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create CMiddleActor
	mMiddleActor = std::make_shared<CMiddleActor>(getGame());
	mMiddleActor->setPosition(getPosition() + Vector3(0.0f, 4.0f, 0.0f));
	mMiddleActor->initailize();
}

void CraneActor::updateActor(float deltatime)
{
	mMiddleActor->setPosition(getPosition() + Vector3(0.0f, 4.0f, 0.0f));
}

void CraneActor::actorInput()
{
	auto game = getGame().lock();

	float sideSpeed = 0.0f;

	if (game->getKeyBoard()->isKeyPressed('b'))
	{
		sideSpeed = 100.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('B'))
	{
		sideSpeed = -100.0f;
	}
	
	mMoveComponent->setSideSpeed(sideSpeed);
}

