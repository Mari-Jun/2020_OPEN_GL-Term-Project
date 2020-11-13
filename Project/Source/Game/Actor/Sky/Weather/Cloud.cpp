#include "Cloud.h"
#include "Snow.h"
#include "../../../Graphics/Window.h"
#include "../../../Game.h"
#include "../../../Component/MoveComponent.h"
#include "../../../Component/BoxComponent.h"
#include "../../../Input/KeyBoard.h"
#include <random>

Cloud::Cloud(const std::weak_ptr<class Game>& game)
	: Actor(game)
	, mSnowing(true)
{
	
}

Cloud::~Cloud()
{

}

void Cloud::initailize()
{
	Actor::initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void Cloud::updateActor(float deltatime)
{
	if (mSnowing)
	{
		std::random_device rd;
		std::mt19937 mersenne(rd());
		std::uniform_int_distribution<> pos(static_cast<int>(-getScale().x), static_cast<int>(getScale().x));

		for (auto i = 0; i < 3; i++)
		{
			auto snow = std::make_shared<Snow>(getGame());
			snow->setPosition(getPosition() + Vector3(pos(mersenne), 0.0f, pos(mersenne)));
			snow->setScale(3.0f);
			snow->initailize();
		}
	}
}

void Cloud::actorInput()
{
	auto game = getGame().lock();

	if (game->getKeyBoard()->isKeyPressed('p'))
	{
		mSnowing = true;
	}
	if (game->getKeyBoard()->isKeyPressed('P'))
	{
		mSnowing = false;
	}
}