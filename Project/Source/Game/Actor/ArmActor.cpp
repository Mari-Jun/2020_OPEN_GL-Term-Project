#include "ArmActor.h"
#include "../Graphics/Window.h"
#include "../Game.h"
#include "../Component/MoveComponent.h"
#include "../Graphics/Mesh/MeshComponent.h"
#include "../Input/KeyBoard.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Renderer/Renderer.h"

ArmActor::ArmActor(const std::weak_ptr<class Game>& game, bool left)
	: Actor(game)
	, mLeft(left)
	, mRad(0.0f)
	, rotPlus(0)
{
	std::cerr << "Create ArmActor\n";
}

ArmActor::~ArmActor()
{
	std::cerr << "Destory ArmActor\n";
}

void ArmActor::initailize()
{
	Actor::initailize();

	setScale(Vector3(2.0f, 6.0f, 2.0f));

	//Create MeshComponent
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer()->shared_from_this());
	mMeshComponent->initailize();
	mMeshComponent->setMesh(getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Box.obj"));
	mMeshComponent->setColor(Vector3(1.0f, 1.0f, 0.0f));

	//Create MoveComponenet
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void ArmActor::updateActor(float deltatime)
{
	float speed = 0.0f;

	setPosition(getPosition() - getUp() * 3);

	if (mLeft)
	{
		Quaternion q = getRotation();
		q = Quaternion::Concatenate(q, Quaternion(getSide(), Math::ToRadians(mRad)));
		setRotation(q);
	}
	else
	{
		Quaternion q = getRotation();
		q = Quaternion::Concatenate(q, Quaternion(getSide(), Math::ToRadians(-mRad)));
		setRotation(q);
	}

	mRad += rotPlus;
	if (mRad >= 90.0f || mRad <= -90.0f)
	{
		rotPlus *= -1;
	}

	setPosition(getPosition() + getUp() * 3);
}

void ArmActor::actorInput()
{
	auto game = getGame().lock();

	if (game->getKeyBoard()->isKeyPressed('t'))
	{
		rotPlus = 1;
	}
	if (game->getKeyBoard()->isKeyPressed('T'))
	{
		rotPlus = -1;
	}
	if (game->getKeyBoard()->isKeyPressed('R'))
	{
		rotPlus = 0;
	}
}

