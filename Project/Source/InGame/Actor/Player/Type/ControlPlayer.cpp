#include "ControlPlayer.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Input/KeyBoard.h"
#include "../../../../Game/Component/MoveComponent.h"

ControlPlayer::ControlPlayer(const std::weak_ptr<class Scene>& scene)
	: Player(scene)
{

}

ControlPlayer::~ControlPlayer()
{

}

void ControlPlayer::initailize()
{
	Player::initailize();
}

void ControlPlayer::updateActor(float deltatime)
{
	Player::updateActor(deltatime);
}

void ControlPlayer::actorInput()
{
	auto game = getGame().lock();

	setMoveSpeed(0.0f);

	if (game->getKeyBoard()->isKeyPressed('w') ||
		game->getKeyBoard()->isKeyPressed('a') ||
		game->getKeyBoard()->isKeyPressed('s') ||
		game->getKeyBoard()->isKeyPressed('d'))
	{
		setMoveSpeed(200.0f);
	}

	if (game->getKeyBoard()->isKeyPressed(32))
	{
		setGravitySpeed(2000.0f);
	}

	mMoveComponent->setForwardSpeed(getMoveSpeed());
}