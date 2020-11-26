#include "Tile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"

Tile::Tile(const std::weak_ptr<class Scene>& scene, TileType type)
	: Actor(scene)
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

std::shared_ptr<class Mesh> Tile::loadMesh() const
{
	std::string meshName;
	switch (mType)
	{
	case Tile::TileType::Basic: meshName = "Asset/Mesh/Tile/Road/Tile"; break;
	case Tile::TileType::Road: meshName = "Asset/Mesh/Tile/Road/Tile_Dirt"; break;
	case Tile::TileType::Light: meshName = "Asset/Mesh/Tile/Road/Tile_Dirt"; break;
	case Tile::TileType::Rock: meshName = "Asset/Mesh/Tile/Road/Tile_Rock"; break;
	case Tile::TileType::Hill: meshName = "Asset/Mesh/Tile/Road/Tile_Hill"; break;
	case Tile::TileType::Crystal: meshName = "Asset/Mesh/Tile/Road/Tile_Crystal"; break;
	case Tile::TileType::Tree: meshName = "Asset/Mesh/Tile/Road/Tile_Tree"; break;
	case Tile::TileType::TreeDouble: meshName = "Asset/Mesh/Tile/Road/Tile_TreeDouble"; break;
	case Tile::TileType::TreeQuad: meshName = "Asset/Mesh/Tile/Road/Tile_TreeQuad"; break;
	case Tile::TileType::StartPoint: meshName = "Asset/Mesh/Tile/Etc/Tile_StartPoint"; break;
	case Tile::TileType::EndPoint: meshName = "Asset/Mesh/Tile/Etc/Tile_EndPoint"; break;
	case Tile::TileType::Snow_Basic: meshName = "Asset/Mesh/Tile/Road/Snow_Tile"; break;
	case Tile::TileType::Snow_Rock: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Rock"; break;
	case Tile::TileType::Snow_Hill: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Hill"; break;
	case Tile::TileType::Snow_Crystal: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Crystal"; break;
	case Tile::TileType::Snow_Tree: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_Tree"; break;
	case Tile::TileType::Snow_TreeDouble: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_TreeDouble"; break;
	case Tile::TileType::Snow_TreeQuad: meshName = "Asset/Mesh/Tile/Road/Snow_Tile_TreeQuad"; break;
	case Tile::TileType::Tower_RoundA: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_RoundA"; break;
	case Tile::TileType::Tower_RoundC: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_RoundC"; break;
	case Tile::TileType::Tower_Blaster: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Blaster"; break;
	case Tile::TileType::Tower_SquareA: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_SquareA"; break;
	case Tile::TileType::Tower_SquareB: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_SquareB"; break;
	case Tile::TileType::Tower_SquareC: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_SquareC"; break;
	case Tile::TileType::Tower_Ballista: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Ballista"; break;
	case Tile::TileType::Tower_Cannon: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Cannon"; break;
	case Tile::TileType::Tower_Catapult: meshName = "Asset/Mesh/Tile/Tower/Tile_Tower_Catapult"; break;
	default: break;
	}
	return getGame().lock()->getRenderer()->getMesh(meshName);
}

std::string Tile::getTileTypeToString() const
{
	switch (mType)
	{
	case Tile::TileType::Basic: return "Basic";
	case Tile::TileType::Road: return "Road";
	case Tile::TileType::Light: return "Light";
	case Tile::TileType::Rock: return "Rock";
	case Tile::TileType::Hill: return "Hill";
	case Tile::TileType::Crystal: return "Crystal";
	case Tile::TileType::Tree: return "Tree";
	case Tile::TileType::TreeDouble: return "TreeDouble";
	case Tile::TileType::TreeQuad: return "TreeQuad";
	case Tile::TileType::StartPoint: return "StartPoint";
	case Tile::TileType::EndPoint: return "EndPoint";
	case Tile::TileType::Snow_Basic: return "SnowBasic";
	case Tile::TileType::Snow_Rock: return "SnowRock";
	case Tile::TileType::Snow_Hill: return "SnowHill";
	case Tile::TileType::Snow_Crystal: return "SnowCrystal";
	case Tile::TileType::Snow_Tree: return "SnowTree";
	case Tile::TileType::Snow_TreeDouble: return "SnowTreeDouble";
	case Tile::TileType::Snow_TreeQuad: return "SnowTreeQuad";
	case Tile::TileType::Tower_RoundA: return "TowerRoundA";
	case Tile::TileType::Tower_RoundC: return "TowerRoundC";
	case Tile::TileType::Tower_Blaster: return "TowerBlaster";
	case Tile::TileType::Tower_SquareA: return "TowerSquareA";
	case Tile::TileType::Tower_SquareB: return "TowerSquareB";
	case Tile::TileType::Tower_SquareC: return "TowerSquareC";
	case Tile::TileType::Tower_Ballista: return "TowerBallista";
	case Tile::TileType::Tower_Cannon: return "TowerCannon";
	case Tile::TileType::Tower_Catapult: return "TowerCatapult";
	default: return "";
	}
}