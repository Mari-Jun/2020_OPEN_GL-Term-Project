#include "ParticleCreater.h"
#include "Snow.h"
#include "../../../Game/Game.h"
#include "../../../Game/Input/KeyBoard.h"
#include <random>

ParticleCreater::ParticleCreater(const std::weak_ptr<class Game>& game)
	: Actor(game)
	, mSnowing(true)
{
	
}

ParticleCreater::~ParticleCreater()
{

}

void ParticleCreater::initailize()
{
	Actor::initailize();
}

void ParticleCreater::updateActor(float deltatime)
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

void ParticleCreater::actorInput()
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