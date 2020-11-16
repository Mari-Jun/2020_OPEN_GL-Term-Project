#include "Ballista.h"
#include "Bow.h"
#include "../../../../Game/Game.h"

Ballista::Ballista(const std::weak_ptr<class Scene>& scene)
	: EnemyTower(scene, EnemyTower::Type::Ballista)
{

}

Ballista::~Ballista()
{

}

void Ballista::initailize()
{
	EnemyTower::initailize();
	/*mBow = std::make_shared<Bow>(getScene());
	mBow->setScale(getScale());
	mBow->setPosition(getPosition() + Vector3::UnitY * getScale().y / 100.0f * 23.0f);
	mBow->initailize();*/
}

void Ballista::updateActor(float deltatime)
{
	chasePlayer();
}

void Ballista::actorInput()
{

}