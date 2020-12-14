//컨트롤 플레이어.cpp
#include "ControlPlayer.h"
#include "../../../../Game/Graphics/Window.h"
#include "../../../../Game/Game.h"
#include "../../../../Game/Input/KeyBoard.h"
#include "../../../../Game/Component/MoveComponent.h"
#include "../../../Scene/GameScene.h"
//#include "../../../Minimap/GameMinimap.h"
#include "../../../Minimap/GameMinimap.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"

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
	auto mMarker = std::make_shared<GameMinimap>(getScene(), getGame().lock()->getRenderer(), weak_from_this(), TRUE);
	mMarker->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/Minimap/mark.png"));
	mMarker->initailize();
}

void ControlPlayer::updateActor(float deltatime)
{
	MovePlayer::updateActor(deltatime);
	//std::cout << getPosition().x << "," << getPosition().y << "," << getPosition().z << std::endl;
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

void ControlPlayer::checkHp()
{
	if (mStat.mHp <= 0.0f)
	{
		//std::dynamic_pointer_cast<class GameScene>(getScene().lock())->stageFail();
	}
}