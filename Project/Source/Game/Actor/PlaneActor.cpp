#include "PlaneActor.h"
#include "../Graphics/Window.h"
#include "../Game.h"
#include "../Component/BoxComponent.h"
#include "../Graphics/Mesh/MeshComponent.h"
#include "../Graphics/Mesh/Mesh.h"

PlaneActor::PlaneActor(const std::weak_ptr<class Scene>& scene)
	: Actor(scene)
{

}

PlaneActor::~PlaneActor()
{
	
}

void PlaneActor::initailize()
{
	Actor::initailize();

	auto game = getGame().lock();

	//Create MeshComponent
	auto mesh = game->getRenderer()->getMesh("Asset/Mesh/Plane");
	//추후에 Box.obj도 넣어서 입체감을 주는 벽과 그냥 평면을 따로 구분해주자.
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), game->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), game->getPhysEngine());
	mBoxComponent->setObjectBox(mesh->getBox());
	mBoxComponent->initailize();
}

void PlaneActor::updateActor(float deltatime)
{

}

void PlaneActor::actorInput()
{

}

void PlaneActor::setPlaneColor(const Vector3& color)
{
	mMeshComponent->setColor(color);
}

void PlaneActor::setTexture(const std::string& fileName)
{
	mMeshComponent->setTexture(fileName);
}