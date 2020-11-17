#include "Snow.h"
#include "../../../Game/Component/MoveComponent.h"
#include "../../../Game/Graphics/Mesh/BillBoardComponent.h"
#include "../../../Game/Actor/Defualt/DefualtShape.h"
#include "../../../Game/Game.h"

Snow::Snow(const std::weak_ptr<class Scene>& scene)
	: Actor(scene)
{

}

Snow::~Snow()
{

}

void Snow::initailize()
{
	Actor::initailize();

	//Create Snow~
	mSnow = std::make_shared<BillBoardComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mSnow->initailize();
	mSnow->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/Particle/snow.png"));

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void Snow::updateActor(float deltatime)
{
	float upSpeed = -200.0f;

	mMoveComponent->setUpSpeed(upSpeed);

	if (getPosition().y <= -30.0f)
	{
		setState(State::Dead);
	}
}

void Snow::actorInput()
{

}