#include "EnemyTile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"
#include "../../Actor/Enemy/EnemyTower.h"

EnemyTile::EnemyTile(const std::weak_ptr<class Scene>& scene, Type type)
	: Tile(scene, type)
{

}

EnemyTile::~EnemyTile()
{
	mEnemy->setState(State::Dead);
}

void EnemyTile::initailize()
{
	Tile::initailize();

	switch (getType())
	{
	case Tile::Type::Tower_Ballista: mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::Type::Ballista); break;
	case Tile::Type::Tower_Blaster : mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::Type::Blaster); break;
	case Tile::Type::Tower_Cannon: mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::Type::Cannon); break;
	case Tile::Type::Tower_Catapult: mEnemy = std::make_shared<EnemyTower>(getScene(), EnemyTower::Type::Catapult); break;
	default: break;
	}

	mEnemy->setScale(getScale() * 1.5f);
	mEnemy->setPosition(getPosition() + Vector3::UnitY * getScale().y);
	mEnemy->initailize();
}
