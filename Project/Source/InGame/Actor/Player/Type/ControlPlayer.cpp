#include "ControlPlayer.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Input/KeyBoard.h"
#include "../../../../Game/Component/MoveComponent.h"

ControlPlayer::ControlPlayer(const std::weak_ptr<class Scene>& scene, PlayerInfo info)
	: MovePlayer(scene, info)
{
	setStat(info);
}

ControlPlayer::~ControlPlayer()
{

}

void ControlPlayer::initailize()
{
	MovePlayer::initailize();
}

void ControlPlayer::updateActor(float deltatime)
{
	MovePlayer::updateActor(deltatime);
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
		updateAnimation();
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