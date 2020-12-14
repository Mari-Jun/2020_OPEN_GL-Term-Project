#include "Tile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"

Tile::Tile(const std::weak_ptr<class Scene>& scene, TileType type)
	: Actor(scene)
	, mType(type)
	, mSeasonType(SeasonType::Green)
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
	std::string meshName = "Asset/Mesh/Tile/";
	switch (mType)
	{
	case Tile::TileType::Road: 
	case Tile::TileType::Light: 
		meshName += "Road/Tile_Dirt"; break;
	case Tile::TileType::StartPoint: meshName = "Asset/Mesh/Tile/Etc/Tile_StartPoint"; break;
	case Tile::TileType::EndPoint: meshName = "Asset/Mesh/Tile/Etc/Tile_EndPoint"; break;
	case Tile::TileType::Basic: 
	case Tile::TileType::Rock:
	case Tile::TileType::Hill: 
	case Tile::TileType::Crystal: 
	case Tile::TileType::Tree: 
	case Tile::TileType::TreeDouble: 
	case Tile::TileType::TreeQuad: 
	case Tile::TileType::Tower_RoundA:
	case Tile::TileType::Tower_RoundC: 
	case Tile::TileType::Tower_Blaster:
	case Tile::TileType::Tower_SquareA: 
	case Tile::TileType::Tower_SquareB:
	case Tile::TileType::Tower_SquareC:
	case Tile::TileType::Tower_Ballista:
	case Tile::TileType::Tower_Cannon: 
	case Tile::TileType::Tower_Catapult:
		meshName += "Road/" + getSeasonTypeToString() + "_Tile"; break;
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

std::string Tile::getSeasonTypeToString() const
{
	switch (mSeasonType)
	{
	case Tile::SeasonType::Sakura: return "Sakura";
	case Tile::SeasonType::Green: return "Green";
	case Tile::SeasonType::Maple: return "Maple";
	case Tile::SeasonType::Snow: return "Snow";
	default: return "";
	}
}