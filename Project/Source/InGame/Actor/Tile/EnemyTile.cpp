#include "EnemyTile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"

#include "../../Actor/Enemy/Tower/EnemyTower.h"
#include "../../Actor/Enemy/Tower/Blaster.h"
#include "../../Actor/Enemy/Tower/Ballista.h"
#include "../../Actor/Enemy/Tower/Cannon.h"
#include "../../Actor/Enemy/Tower/Catapult.h"

EnemyTile::EnemyTile(const std::weak_ptr<class Game>& game, Type type)
	: Tile(game, type)
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
	case Tile::Type::Tower_Ballista: mEnemy = std::make_shared<Ballista>(getGame()); break;
	case Tile::Type::Tower_Blaster : mEnemy = std::make_shared<Blaster>(getGame()); break;
	case Tile::Type::Tower_Cannon: mEnemy = std::make_shared<Cannon>(getGame()); break;
	case Tile::Type::Tower_Catapult: mEnemy = std::make_shared<Catapult>(getGame()); break;
	default:
		break;
	}

	mEnemy->setScale(getScale());
	mEnemy->setPosition(getPosition() + Vector3::UnitY * getScale().y);
	mEnemy->initailize();
}

void EnemyTile::updateActor(float deltatime)
{

}

void EnemyTile::actorInput()
{

}
