#include "DefaultMinion.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Component/MoveComponent.h"

DefaultMinion::DefaultMinion(const std::weak_ptr<class Scene>& scene)
	: Player(scene)
{

}

DefaultMinion::~DefaultMinion()
{

}

void DefaultMinion::initailize()
{
	Player::initailize();
	setPlayerTexture("Asset/Mesh/Player/skin_robot.png");
	setMoveSpeed(50.0f);		
}

void DefaultMinion::updateActor(float deltatime)
{
	Player::updateActor(deltatime);
}

void DefaultMinion::actorInput()
{
	auto game = getGame().lock();

	mMoveComponent->setForwardSpeed(getMoveSpeed());
}