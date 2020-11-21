#include "RobotHead.h"
#include "../../../../Game/Component/BoxComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Game.h"

RobotHead::RobotHead(const std::weak_ptr<class Scene>& scene)
	: Actor(scene, Type::Etc)
{

}

RobotHead::~RobotHead()
{

}

void RobotHead::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Player/PlayerHead");
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), getGame().lock()->getPhysEngine());
	mBoxComponent->setObjectBox(mesh->getBox());
	mBoxComponent->initailize();
}

void RobotHead::updateActor(float deltatime)
{

}

void RobotHead::actorInput()
{
	
}

void RobotHead::setPlayerTexture(const std::string& fileName, int index)
{
	mMeshComponent->setTexture(fileName);
	mMeshComponent->setTextureIndex(index);
}