#include "EnemyTile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"
#include "../../Actor/Enemy/EnemyTower.h"

EnemyTile::EnemyTile(const std::weak_ptr<class Scene>& scene, TileType type)
	: OrnamentTile(scene, type)
{

}

EnemyTile::~EnemyTile()
{
	mEnemy->setState(State::Dead);
}

void EnemyTile::initailize()
{
	OrnamentTile::initailize();

	switch (getTileType())
	{
	case Tile::TileType::Tower_Ballista: mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::EnemyType::Ballista); break;
	case Tile::TileType::Tower_Blaster : mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::EnemyType::Blaster); break;
	case Tile::TileType::Tower_Cannon: mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::EnemyType::Cannon); break;
	case Tile::TileType::Tower_Catapult: mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::EnemyType::Catapult); break;
	default: break;
	}

	mEnemy->setScale(getScale() * 1.5f);
	mEnemy->setPosition(getPosition() + Vector3::UnitY * getScale().y);
	mEnemy->initailize();
}
