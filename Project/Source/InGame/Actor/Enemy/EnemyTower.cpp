#include "EnemyTower.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/MoveComponent.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../Scene/EditScene.h"
#include "../../Scene/GameScene.h"
#include "../../Map/GameMap.h"

#include "Weapon.h"
#include "../../Actor/Enemy/Weapon/Blaster.h"
#include "../../Actor/Enemy/Weapon/Ballista.h"
#include "../../Actor/Enemy/Weapon/Cannon.h"
#include "../../Actor/Enemy/Weapon/Catapult.h"

EnemyTower::EnemyTower(const std::weak_ptr<class Scene>& scene, EnemyType type)
	: Actor(scene)
	, mType(type)
{

}

EnemyTower::~EnemyTower()
{
	if (!mWeapon.expired())
	{
		mWeapon.lock()->setState(State::Dead);
	}
}

void EnemyTower::initailize()
{
	Actor::initailize();

	auto mesh = loadMesh();
	if (mesh != nullptr)
	{
		mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
		mMeshComponent->setMesh(mesh);
		mMeshComponent->initailize();
	}

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create Weapon
	createWeapon();
}

void EnemyTower::updateActor(float deltatime)
{
	findPlayer();
	chasePlayer();

	switch (mType)
	{
	case EnemyTower::EnemyType::Ballista: mWeapon.lock()->setPosition(getPosition() + Vector3::UnitY * getScale().y / 100.0f * 23.0f); break;
	case EnemyTower::EnemyType::Blaster: break;
	case EnemyTower::EnemyType::Cannon: mWeapon.lock()->setPosition(getPosition() + Vector3::UnitY * getScale().y / 100.0f * 20.0f); break;
	case EnemyTower::EnemyType::Catapult: mWeapon.lock()->setPosition(getPosition() + Vector3::UnitY * getScale().y / 100.0f * 22.0f); break;
	default: break;
	}
}

void EnemyTower::actorInput()
{

}

std::shared_ptr<class Mesh> EnemyTower::loadMesh() const
{
	if (mType != EnemyType::Blaster)
	{
		std::string meshName;
		meshName = "Asset/Mesh/Enemy/Weapon_Base";
		return getGame().lock()->getRenderer()->getMesh(meshName);
	}
	else
		return nullptr;	
}

void EnemyTower::createWeapon()
{
	std::shared_ptr<Weapon> weapon;
	std::string meshName;
	switch (mType)
	{
	case EnemyTower::EnemyType::Ballista: 
		weapon = std::make_shared<Ballista>(getScene()); 
		weapon->setPosition(getPosition() + Vector3::UnitY * getScale().y / 100.0f * 23.0f);
		meshName = "Asset/Mesh/Enemy/Weapon_Ballista"; 
		break;
	case EnemyTower::EnemyType::Blaster: 
		weapon = std::make_shared<Blaster>(getScene());  
		weapon->setPosition(getPosition());
		meshName = "Asset/Mesh/Enemy/Weapon_Blaster";
		break;
	case EnemyTower::EnemyType::Cannon: 
		weapon = std::make_shared<Cannon>(getScene());  
		weapon->setPosition(getPosition() + Vector3::UnitY * getScale().y / 100.0f * 20.0f);
		meshName = "Asset/Mesh/Enemy/Weapon_Cannon"; 
		break;
	case EnemyTower::EnemyType::Catapult:
		weapon = std::make_shared<Catapult>(getScene());
		weapon->setPosition(getPosition() + Vector3::UnitY * getScale().y / 100.0f * 22.0f);
		meshName = "Asset/Mesh/Enemy/Weapon_Catapult"; 
		break;
	default: break;
	}

	auto meshComp = std::make_shared<MeshComponent>(weapon, getGame().lock()->getRenderer());
	meshComp->setMesh(getGame().lock()->getRenderer()->getMesh(meshName));
	meshComp->initailize();

	weapon->setScale(getScale());
	weapon->initailize();

	auto objectOwner = std::dynamic_pointer_cast<GameScene>(getScene().lock());

	if (objectOwner.use_count())
	{
		weapon->setEffectIndex(objectOwner->getGameMap()->getAttackTowerCount());
	}
	else {//에디트씬에선 머 공격할것도아닌데 해줄 이유가 없음
		//weapon->setEffectIndex(std::dynamic_pointer_cast<EditScene>(getScene().lock())->getGameMap()->getAttackTowerCount());
	}

	mWeapon = weapon;

}

void EnemyTower::findPlayer()
{
	const auto& players = getScene().lock()->getActors(Actor::getTypeToString(Actor::Type::Player));
	float maxLength = mWeapon.lock()->getAttackRange();
	std::shared_ptr<class Actor> target = nullptr;

	for (const auto& p : players)
	{
		auto dist = p->getPosition() - getPosition();
		auto length = dist.Length();

		if (maxLength > length)
		{
			target = p;
			maxLength = length;
		}
	}

	mWeapon.lock()->setTarget(target);
}

void EnemyTower::chasePlayer()
{	
	const auto& target = mWeapon.lock()->getTarget();

	if (!target.expired())
	{
		Vector3 toVec = target.lock()->getPosition() - getPosition();
		toVec.y = 0.0f;
		toVec.Normalize();
		rotateToNewForwardNotY(toVec);
	}
}

std::string EnemyTower::getEnemyTypeToString() const
{
	switch (mType)
	{
	case EnemyTower::EnemyType::Ballista: return "Ballista";
	case EnemyTower::EnemyType::Blaster: return "Blaster";
	case EnemyTower::EnemyType::Cannon: return "Cannon";
	case EnemyTower::EnemyType::Catapult: return "Catapult";
	default: return"";
	}
}