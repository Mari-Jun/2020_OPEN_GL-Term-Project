#include "DefualtShape.h"
#include "../../Graphics/Window.h"
#include "../../Game.h"
#include "../../Component/MoveComponent.h"
#include "../../Component/BoxComponent.h"
#include "../../Graphics/Mesh/MeshComponent.h"
#include "../../Input/KeyBoard.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../PlaneActor.h"

DefualtShape::DefualtShape(const std::weak_ptr<class Game>& game, Shape shape)
	: Actor(game)
	, mShape(shape)
{
	std::cerr << "Create DefualtShape\n";
}

DefualtShape::~DefualtShape()
{
	std::cerr << "Destory DefualtShape\n";
}

void DefualtShape::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	std::shared_ptr<Mesh> mesh;
	switch (mShape)
	{
	case DefualtShape::Shape::Box:
		mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Box.obj");
		break;
	case DefualtShape::Shape::Sphere:
		mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Sphere.obj");
		break;
	case DefualtShape::Shape::Slinder:
		mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Slinder.obj");
		break;
	default:
		break;
	}

	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->initailize();
	mMeshComponent->setMesh(mesh);
	mMeshComponent->setColor(mMeshColor);

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), getGame().lock()->getPhysEngine());
	mBoxComponent->setObjectBox(mesh->getBox());
	mBoxComponent->initailize();
}

void DefualtShape::updateActor(float deltatime)
{

}

void DefualtShape::actorInput()
{

}