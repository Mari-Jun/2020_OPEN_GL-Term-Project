#include "EnemyTower.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Game.h"

EnemyTower::EnemyTower(const std::weak_ptr<class Game>& game, Type type)
	: Actor(game)
	, mType(type)
{

}

EnemyTower::~EnemyTower()
{

}

void EnemyTower::initailize()
{
	Actor::initailize();

	auto mesh = loadMesh();
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void EnemyTower::updateActor(float deltatime)
{

}

void EnemyTower::actorInput()
{

}

std::shared_ptr<class Mesh> EnemyTower::loadMesh() const
{
	std::string meshName;
	switch (mType)
	{
	case EnemyTower::Type::Ballista: meshName = "Asset/Mesh/Enemy/Weapon_Ballista"; break;
	case EnemyTower::Type::Blaster: meshName = "Asset/Mesh/Enemy/Weapon_Blaster"; break;
	case EnemyTower::Type::Cannon: meshName = "Asset/Mesh/Enemy/Weapon_Cannon"; break;
	case EnemyTower::Type::Catapult: meshName = "Asset/Mesh/Enemy/Weapon_Catapult"; break;
	default: break;
	}
	return getGame().lock()->getRenderer()->getMesh(meshName);
}

std::string EnemyTower::getTypeToString() const
{
	switch (mType)
	{
	case EnemyTower::Type::Ballista: return "Ballista";
	case EnemyTower::Type::Blaster: return "Blaster";
	case EnemyTower::Type::Cannon: return "Cannon";
	case EnemyTower::Type::Catapult: return "Catapult";
	default: return"";
	}
}