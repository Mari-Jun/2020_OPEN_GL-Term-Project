#include "Projectile.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Game.h"

Projectile::Projectile(const std::weak_ptr<class Scene>& scene, Type type)
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
	case Projectile::Type::Arrow: meshName = "Asset/Mesh/Enemy/Arrow"; break;
	case Projectile::Type::CannonBall: meshName = "Asset/Mesh/Enemy/Arrow"; break;
	case Projectile::Type::Rock: meshName = "Asset/Mesh/Enemy/Arrow"; break;
	case Projectile::Type::Raser: meshName = "Asset/Mesh/Enemy/Arrow"; break;
	default: break;
	}
	return getGame().lock()->getRenderer()->getMesh(meshName);
}

std::string Projectile::getTypeToString() const
{
	switch (mType)
	{
	case Projectile::Type::Arrow: return "Arrow";
	case Projectile::Type::CannonBall: return "CannonBall";
	case Projectile::Type::Rock: return "Rock";
	case Projectile::Type::Raser: return "Raser";
	default: return"";
	}
}