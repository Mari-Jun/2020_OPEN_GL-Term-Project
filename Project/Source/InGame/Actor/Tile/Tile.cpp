#include "Tile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"

Tile::Tile(const std::weak_ptr<class Game>& game, Type type)
	: Actor(game)
	, mType(type)
{
	
}

Tile::~Tile()
{

}

void Tile::initailize()
{
	Actor::initailize();

	auto mesh = loadMesh();
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), getGame().lock()->getPhysEngine());
	mBoxComponent->setObjectBox(mesh->getBox());
	mBoxComponent->initailize();
}

void Tile::updateActor(float deltatime)
{

}

void Tile::actorInput()
{

}

std::shared_ptr<class Mesh> Tile::loadMesh() const
{
	std::string meshName;
	switch (mType)
	{
	case Tile::Type::Basic:
		meshName = "Asset/Mesh/Tile/Road/Tile";
		break;
	default:
		meshName = "";
		break;
	}
	return getGame().lock()->getRenderer()->getMesh(meshName);
}