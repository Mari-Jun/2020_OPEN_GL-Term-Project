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
	case Tile::Type::Basic: meshName = "Asset/Mesh/Tile/Road/Tile"; break;
	case Tile::Type::Road: meshName = "Asset/Mesh/Tile/Road/Tile_Dirt"; break;
	case Tile::Type::Rock: meshName = "Asset/Mesh/Tile/Road/Tile_Rock"; break;
	case Tile::Type::Hill: meshName = "Asset/Mesh/Tile/Road/Tile_Hill"; break;
	case Tile::Type::Crystal: meshName = "Asset/Mesh/Tile/Road/Tile_Crystal"; break;
	case Tile::Type::Tree: meshName = "Asset/Mesh/Tile/Road/Tile_Tree"; break;
	case Tile::Type::TreeDouble: meshName = "Asset/Mesh/Tile/Road/Tile_TreeDouble"; break;
	case Tile::Type::TreeQuad: meshName = "Asset/Mesh/Tile/Road/Tile_TreeQuad"; break;
	case Tile::Type::StartPoint: meshName = "Asset/Mesh/Tile/Etc/Tile_StartPoint"; break;
	case Tile::Type::EndPoint: meshName = "Asset/Mesh/Tile/Etc/Tile_EndPoint"; break;
	case Tile::Type::Snow_Basic: meshName = "Asset/Mesh/Tile/Road/Snow_Tile"; break;
	case Tile::Type::Snow_Rock: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Rock"; break;
	case Tile::Type::Snow_Hill: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Hill"; break;
	case Tile::Type::Snow_Crystal: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Crystal"; break;
	case Tile::Type::Snow_Tree: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Tree"; break;
	case Tile::Type::Snow_TreeDouble: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_TreeDouble"; break;
	case Tile::Type::Snow_TreeQuad: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_TreeQuad"; break;
	case Tile::Type::Tower_RoundA: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_RoundA"; break;
	case Tile::Type::Tower_RoundC: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_RoundC"; break;
	case Tile::Type::Tower_Blaster: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Blaster"; break;
	case Tile::Type::Tower_SquareA: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_SquareA"; break;
	case Tile::Type::Tower_SquareB: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_SquareB"; break;
	case Tile::Type::Tower_SquareC: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_SquareC"; break;
	case Tile::Type::Tower_Ballista: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Ballista"; break;
	case Tile::Type::Tower_Cannon: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Cannon"; break;
	case Tile::Type::Tower_Catapult: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Catapult"; break;
	default: break;
	}
	return getGame().lock()->getRenderer()->getMesh(meshName);
}

std::string Tile::getTypeToString() const
{
	switch (mType)
	{
	case Tile::Type::Basic: return "Basic";
	case Tile::Type::Road: return "Road";
	case Tile::Type::Rock: return "Rock";
	case Tile::Type::Hill: return "Hill";
	case Tile::Type::Crystal: return "Crystal";
	case Tile::Type::Tree: return "Tree";
	case Tile::Type::TreeDouble: return "TreeDouble";
	case Tile::Type::TreeQuad: return "TreeQuad";
	case Tile::Type::StartPoint: return "StartPoint";
	case Tile::Type::EndPoint: return "EndPoint";
	case Tile::Type::Snow_Basic: return "SnowBasic";
	case Tile::Type::Snow_Rock: return "SnowRock";
	case Tile::Type::Snow_Hill: return "SnowHill";
	case Tile::Type::Snow_Crystal: return "SnowCrystal";
	case Tile::Type::Snow_Tree: return "SnowTree";
	case Tile::Type::Snow_TreeDouble: return "SnowTreeDouble";
	case Tile::Type::Snow_TreeQuad: return "SnowTreeQuad";
	case Tile::Type::Tower_RoundA: return "TowerRoundA";
	case Tile::Type::Tower_RoundC: return "TowerRoundC";
	case Tile::Type::Tower_Blaster: return "TowerBlaster";
	case Tile::Type::Tower_SquareA: return "TowerSquareA";
	case Tile::Type::Tower_SquareB: return "TowerSquareB";
	case Tile::Type::Tower_SquareC: return "TowerSquareC";
	case Tile::Type::Tower_Ballista: return "TowerBallista";
	case Tile::Type::Tower_Cannon: return "TowerCannon";
	case Tile::Type::Tower_Catapult: return "TowerCatapult";
	default: return "";
	}
}