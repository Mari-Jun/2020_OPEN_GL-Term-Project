#include "RobotHead.h"
#include "../../Graphics/Window.h"
#include "../../Game.h"
#include "../../Component/MoveComponent.h"
#include "../../Component/BoxComponent.h"
#include "../../Graphics/Mesh/MeshComponent.h"
#include "../../Input/KeyBoard.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../PlaneActor.h"

RobotHead::RobotHead(const std::weak_ptr<class Game>& game)
	: Actor(game)
{
	std::cerr << "Create RobotHead\n";
}

RobotHead::~RobotHead()
{
	std::cerr << "Destory RobotHead\n";
}

void RobotHead::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Box.obj");
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->initailize();
	mMeshComponent->setMesh(mesh);
	mMeshComponent->setColor(mMeshColor);
}

void RobotHead::createNose()
{
	//Create Nose
	mNose = std::make_shared<RobotHead>(getGame());
	mNose->setScale(2.0f);
	mNose->setMeshColor(Vector3(0.0f, 0.0f, 1.0f));
	mNose->initailize();
}

void RobotHead::updateActor(float deltatime)
{
	if (mNose != nullptr)
	{
		mNose->setPosition(getPosition() + getForward() * (mNose->getScale() + getScale()) / 2);
	}
}

void RobotHead::actorInput()
{
	
}