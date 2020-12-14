#include "OrnamentTile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"
#include "../../Actor/Enemy/EnemyTower.h"

OrnamentTile::OrnamentTile(const std::weak_ptr<class Scene>& scene, TileType type)
	: Tile(scene, type)
{

}

OrnamentTile::~OrnamentTile()
{
	
}

void OrnamentTile::initailize()
{
	Tile::initailize();

	setOrnament();
}

void OrnamentTile::setOrnament()
{
	std::string meshName = "Asset/Mesh/Tile/";
	switch (getTileType())
	{
	case Tile::TileType::Rock: meshName += "Road/" + getSeasonTypeToString() + "_Tile_Rock"; break;
	case Tile::TileType::Hill: meshName += "Road/" + getSeasonTypeToString() + "_Tile_Hill"; break;
	case Tile::TileType::Crystal: meshName += "Road/" + getSeasonTypeToString() + "_Tile_Crystal"; break;
	case Tile::TileType::Tree: meshName += "Road/" + getSeasonTypeToString() + "_Tile_Tree"; break;
	case Tile::TileType::TreeDouble: meshName += "Road/" + getSeasonTypeToString() + "_Tile_TreeDouble"; break;
	case Tile::TileType::TreeQuad: meshName += "Road/" + getSeasonTypeToString() + "_Tile_TreeQuad"; break;
	case Tile::TileType::Tower_RoundA: meshName += "Tower/Tile_Tower_RoundA"; break;
	case Tile::TileType::Tower_RoundC: meshName += "Tower/Tile_Tower_RoundC"; break;
	case Tile::TileType::Tower_Blaster: meshName += "Tower/Tile_Tower_Blaster"; break;
	case Tile::TileType::Tower_SquareA: meshName += "Tower/Tile_Tower_SquareA"; break;
	case Tile::TileType::Tower_SquareB: meshName += "Tower/Tile_Tower_SquareB"; break;
	case Tile::TileType::Tower_SquareC: meshName += "Tower/Tile_Tower_SquareC"; break;
	case Tile::TileType::Tower_Ballista: meshName += "Tower/Tile_Tower_Ballista"; break;
	case Tile::TileType::Tower_Cannon: meshName += "Tower/Tile_Tower_Cannon"; break;
	case Tile::TileType::Tower_Catapult: meshName += "Tower/Tile_Tower_Catapult"; break;
	default:
		break;
	}

	auto mesh = getGame().lock()->getRenderer()->getMesh(meshName);
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();
}