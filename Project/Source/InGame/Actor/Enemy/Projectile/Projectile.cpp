#include "Projectile.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Game.h"

Projectile::Projectile(const std::weak_ptr<class Scene>& scene, PjtType type)
	: Actor(scene)
	, mType(type)
{

}

Projectile::~Projectile()
{

}

void Projectile::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	auto mesh = loadMesh();
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void Projectile::updateActor(float deltatime)
{
	
}

void Projectile::actorInput()
{

}

void Projectile::collide()
{

}

std::shared_ptr<class Mesh> Projectile::loadMesh() const
{
	std::string meshName;
	switch (mType)
	{
	case Projectile::PjtType::Arrow: meshName = "Asset/Mesh/Enemy/Arrow"; break;
	case Projectile::PjtType::CannonBall: meshName = "Asset/Mesh/Enemy/cannonball"; break;
	case Projectile::PjtType::Rock: meshName = "Asset/Mesh/Enemy/stone"; break;
	case Projectile::PjtType::Laser: meshName = "Asset/Mesh/Enemy/Arrow"; break;
	default: break;
	}
	return getGame().lock()->getRenderer()->getMesh(meshName);
}

std::string Projectile::getPjtTypeToString() const
{
	switch (mType)
	{
	case Projectile::PjtType::Arrow: return "Arrow";
	case Projectile::PjtType::CannonBall: return "CannonBall";
	case Projectile::PjtType::Rock: return "Rock";
	case Projectile::PjtType::Laser: return "Laser";
	default: return"";
	}
}