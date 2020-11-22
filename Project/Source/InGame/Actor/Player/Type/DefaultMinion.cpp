#include "DefaultMinion.h"
#include "../../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../../Game/Graphics/Mesh/BillBoardComponent.h"	

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

	////Create HealthBar
	//mHealthBar = std::make_shared<Actor>(getScene(), Type::Ui);
	//auto hp = std::make_shared<BillBoardComponent>(mHealthBar, getGame().lock()->getRenderer());
	//hp->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/Player/RedBar.png"));
	//hp->initailize();
	//mHealthBar->setScale(0.1f);
	//mHealthBar->setPosition(getPosition() + Vector3::UnitY * 10.0f);
	//mHealthBar->initailize();

}

void DefaultMinion::updateActor(float deltatime)
{
	Player::updateActor(deltatime);

	//mHealthBar->setRotation(getRotation());
	//mHealthBar->setPosition(getPosition() + Vector3::UnitY * 10.0f);
	//std::cout << mHealthBar->getPosition().x << ", " << mHealthBar->getPosition().y << ", " << mHealthBar->getPosition().z << std::endl;
}

void DefaultMinion::actorInput()
{
	auto game = getGame().lock();

	mMoveComponent->setForwardSpeed(getMoveSpeed());
}