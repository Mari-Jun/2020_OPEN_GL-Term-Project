#include "AlphaShape.h"
#include "../../Graphics/Window.h"
#include "../../Game.h"
#include "../../Component/MoveComponent.h"
#include "../../Component/BoxComponent.h"
#include "../../Graphics/Mesh/AlphaComponent.h"
#include "../../Input/KeyBoard.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../PlaneActor.h"

AlphaShape::AlphaShape(const std::weak_ptr<class Scene>& scene, Shape shape, bool collides)
	: Actor(scene)
	, mShape(shape)
	, mCollides(collides)
{

}

AlphaShape::~AlphaShape()
{

}

void AlphaShape::initailize()
{
	Actor::initailize();

	auto game = getGame().lock();

	//Create AlphaComponent
	std::shared_ptr<Mesh> mesh;
	switch (mShape)
	{
	case AlphaShape::Shape::Box:
		mesh = game->getRenderer()->getMesh("Asset/Mesh/Box");
		break;
	case AlphaShape::Shape::Sphere:
		mesh = game->getRenderer()->getMesh("Asset/Mesh/Sphere");
		break;
	case AlphaShape::Shape::Slinder:
		mesh = game->getRenderer()->getMesh("Asset/Mesh/Slinder");
		break;
	case AlphaShape::Shape::Pyramid:
		mesh = game->getRenderer()->getMesh("Asset/Mesh/Pyramid");
		break;
	default:
		break;
	}

	mAlphaComponent = std::make_shared<AlphaComponent>(weak_from_this(), game->getRenderer());
	mAlphaComponent->initailize();
	mAlphaComponent->setMesh(mesh);
	mAlphaComponent->setColor(mMeshColor);


	//Create BoxComponent
	if (mCollides)
	{
		mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), game->getPhysEngine());
		mBoxComponent->setObjectBox(mesh->getBox());
		mBoxComponent->initailize();
	}

}

void AlphaShape::updateActor(float deltatime)
{

}

void AlphaShape::actorInput()
{

}

void AlphaShape::setTexture(const std::string& fileName)
{
	mAlphaComponent->setTexture(fileName);
}