#include "EnemyTower.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/MoveComponent.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"

EnemyTower::EnemyTower(const std::weak_ptr<class Scene>& scene, Type type)
	: Actor(scene)
	, mType(type)
	, mAttackRange(600.0f)
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
	findPlayer();
	chasePlayer();
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
	case EnemyTower::Type::Ballista_Bow:  meshName = "Asset/Mesh/Enemy/Weapon_Ballista_Bow"; break;
	case EnemyTower::Type::Blaster: meshName = "Asset/Mesh/Enemy/Weapon_Blaster"; break;
	case EnemyTower::Type::Cannon: meshName = "Asset/Mesh/Enemy/Weapon_Cannon"; break;
	case EnemyTower::Type::Catapult: meshName = "Asset/Mesh/Enemy/Weapon_Catapult"; break;
	default: break;
	}
	return getGame().lock()->getRenderer()->getMesh(meshName);
}

void EnemyTower::findPlayer()
{
	const auto& players = getScene().lock()->getActors(Actor::getTypeToString(Actor::Type::Player));
	mTarget.reset();
	float maxLength = mAttackRange;

	for (const auto& p : players)
	{
		auto dist = p->getPosition() - getPosition();
		auto length = dist.Length();

		if (maxLength > length)
		{
			mTarget = p;
			maxLength = length;
		}
	}
}

void EnemyTower::chasePlayer()
{	
	float angluarSpeed = 0.0f;

	if (!mTarget.expired())
	{
		Vector3 toVec = mTarget.lock()->getPosition() - getPosition();
		toVec.Normalize();

		auto a = toVec;
		auto b = getForward();

		a.y = b.y = 0.0f;
		a.Normalize();
		b.Normalize();

		auto rad = Math::Acos(Vector3::Dot(a, b));

		if (!Math::NearZero(rad))
		{
			if (Vector3::Cross(a, b).y > 0.0f)
				angluarSpeed = -1.0f;
			else
				angluarSpeed = 1.0f;
		}
	}

	mMoveComponent->setAngularSpeed(angluarSpeed);
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