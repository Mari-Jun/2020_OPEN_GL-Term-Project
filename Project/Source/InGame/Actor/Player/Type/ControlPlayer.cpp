#include "ControlPlayer.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Input/KeyBoard.h"
#include "../../../../Game/Component/MoveComponent.h"

ControlPlayer::ControlPlayer(const std::weak_ptr<class Scene>& scene)
	: Player(scene, PlayerType::Control)
{

}

ControlPlayer::~ControlPlayer()
{

}

void ControlPlayer::initailize()
{
	Player::initailize();
	setPlayerTexture("Asset/Mesh/Player/skin_man.png");
}

void ControlPlayer::updateActor(float deltatime)
{
	Player::updateActor(deltatime);
}

void ControlPlayer::actorInput()
{
	auto game = getGame().lock();

	mStat.mSpeed = 0.0f;

	if (game->getKeyBoard()->isKeyPressed('w') ||
		game->getKeyBoard()->isKeyPressed('a') ||
		game->getKeyBoard()->isKeyPressed('s') ||
		game->getKeyBoard()->isKeyPressed('d'))
	{
		mStat.mSpeed = 200.0f;
	}

	if (game->getKeyBoard()->isKeyPressed(32))
	{
		setGravitySpeed(2000.0f);
	}

	mMoveComponent->setForwardSpeed(mStat.mSpeed);
}