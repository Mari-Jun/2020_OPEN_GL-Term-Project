#include "ControlPlayer.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Input/KeyBoard.h"
#include "../../../../Game/Component/MoveComponent.h"

ControlPlayer::ControlPlayer(const std::weak_ptr<class Scene>& scene, PlayerInfo info)
	: Player(scene, info, PlayerType::Control)
{
	setStat(info);
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
	auto speed = 0.0f;

	if (game->getKeyBoard()->isKeyPressed('w') ||
		game->getKeyBoard()->isKeyPressed('a') ||
		game->getKeyBoard()->isKeyPressed('s') ||
		game->getKeyBoard()->isKeyPressed('d'))
	{
		speed = mStat.mSpeed;
	}

	if (game->getKeyBoard()->isKeyPressed(32))
	{
		setGravitySpeed(2000.0f);
	}

	mMoveComponent->setForwardSpeed(speed);
}

void ControlPlayer::setStat(PlayerInfo info)
{
	mStat.mMaxHp = static_cast<float>(info.getHpStat());
	mStat.mDef = static_cast<float>(info.getDefStat());
	mStat.mSpeed = static_cast<float>(info.getSpeedStat());
	mStat.mHp = mStat.mMaxHp;
}