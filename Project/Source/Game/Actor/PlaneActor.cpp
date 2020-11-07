#include "PlaneActor.h"
#include "../Graphics/Window.h"
#include "../Game.h"
#include "../Component/BoxComponent.h"
#include "../Graphics/Mesh/MeshComponent.h"
#include "../Graphics/Mesh/Mesh.h"

PlaneActor::PlaneActor(const std::weak_ptr<class Game>& game)
	: Actor(game)
{
	std::cerr << "Create PlaneActor\n";
}

PlaneActor::~PlaneActor()
{
	std::cerr << "Destory PlaneActor\n";
	getGame().lock()->removePlane(std::dynamic_pointer_cast<PlaneActor>(weak_from_this().lock()));
}

void PlaneActor::initailize()
{
	Actor::initailize();

	auto game = getGame().lock();

	//Create MeshComponent
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Plane.obj");
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), game->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), game->getPhysEngine());
	mBoxComponent->setObjectBox(mesh->getBox());
	mBoxComponent->initailize();

	game->addPlane(std::dynamic_pointer_cast<PlaneActor>(shared_from_this()));
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