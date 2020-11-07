#include "Snow.h"
#include "../../../Graphics/Window.h"
#include "../../../Game.h"
#include "../../../Component/MoveComponent.h"
#include "../../Defualt/DefualtShape.h"

Snow::Snow(const std::weak_ptr<class Game>& game)
	: Actor(game)
{

}

Snow::~Snow()
{

}

void Snow::initailize()
{
	Actor::initailize();

	//Create Snow~
	mSnow = std::make_shared<DefualtShape>(getGame(), DefualtShape::Shape::Box, false);
	mSnow->setScale(getScale());
	mSnow->setRotation(getRotation());
	mSnow->setPosition(getPosition());
	mSnow->setMeshColor(Vector3::Rgb(Vector3(256.0f, 256.0f, 256.0f)));
	mSnow->initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void Snow::updateActor(float deltatime)
{
	mSnow->setPosition(getPosition());

	float upSpeed = -200.0f;

	mMoveComponent->setUpSpeed(upSpeed);

	if (getPosition().y <= -50.0f)
	{
		setState(State::Dead);
		mSnow->setState(State::Dead);
	}
}

void Snow::actorInput()
{

}