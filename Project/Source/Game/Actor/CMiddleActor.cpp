#include "CMiddleActor.h"
#include "../Graphics/Window.h"
#include "../Game.h"
#include "../Component/MoveComponent.h"
#include "../Graphics/Mesh/MeshComponent.h"
#include "../Input/KeyBoard.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Renderer/Renderer.h"
#include "ArmActor.h"

CMiddleActor::CMiddleActor(const std::weak_ptr<class Game>& game)
	: Actor(game)
{
	std::cerr << "Create CMiddleActor\n";
}

CMiddleActor::~CMiddleActor()
{
	std::cerr << "Destory CMiddleActor\n";
}

void CMiddleActor::initailize()
{
	Actor::initailize();

	setScale(Vector3(10.0f, 2.0f, 10.0f));

	//Create MeshComponent
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer()->shared_from_this());
	mMeshComponent->initailize();
	mMeshComponent->setMesh(getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Box.obj"));
	mMeshComponent->setColor(Vector3(1.0f, 0.0f, 1.0f));

	//Create MoveComponenet
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create Arm
	mLeftArm = std::make_shared<ArmActor>(getGame(), true);
	mLeftArm->initailize();
	mRightArm = std::make_shared<ArmActor>(getGame(), false);
	mRightArm->initailize();
}

void CMiddleActor::updateActor(float deltatime)
{
	mLeftArm->setPosition(getPosition() + Vector3::Transform(Vector3(-2.0f, 4.0f, 0.0f), getRotation()));
	mLeftArm->setRotation(getRotation());
	mRightArm->setPosition(getPosition() + Vector3::Transform(Vector3(2.0f, 4.0f, 0.0f), getRotation()));
	mRightArm->setRotation(getRotation());
}

void CMiddleActor::actorInput()
{
	auto game = getGame().lock();
	
	float angluarSpeed = 0.0f;

	if (game->getKeyBoard()->isKeyPressed('m'))
	{
		angluarSpeed = -Math::TwoPi / 5;
	}
	if (game->getKeyBoard()->isKeyPressed('M'))
	{
		angluarSpeed = Math::TwoPi / 5;
	}

	mMoveComponent->setAngularSpeed(angluarSpeed);
}

