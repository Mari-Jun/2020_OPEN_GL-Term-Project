#include "MinionManager.h"
#include "MinionAi.h"
#include "../../../../../Game/Game.h"
#include "../../../../../Game/Sound/Sound.h"
#include "../../../../../Game/Input/KeyBoard.h"
#include "../../../../Map/GameMap.h"
#include "../DefaultMinion.h"
#include "../../../../Scene/GameScene.h"
#include "../../../../UI/HUD/GameHUD.h"

MinionManager::MinionManager(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class GameMap>& gameMap, const PlayerInfo& info)
	: Actor(scene)
	, mGameMap(gameMap)
	, mInfo(info)
	, mDelay(0.0f)
	, mCreateMinionNum(mGameMap.lock()->getMinionCount())
	, mLiveMinionNum(0)
	, mClearMinionNum(mCreateMinionNum / 4)
{

}

MinionManager::~MinionManager()
{

}

void MinionManager::initailize()
{
	Actor::initailize();

	mMinionAi = std::make_shared<MinionAi>(getScene());
	auto map = mGameMap.lock();
	mMinionAi->initailize(map->getTiles(), map->getStartPosIndex(), map->getEndPosIndex(), map->getTileSize(), map->getMapSize());
}

void MinionManager::updateActor(float deltatime)
{
	if (mCreateMinionNum > 0)
	{
		mDelay -= deltatime;
		createMinion();
	}
}

void MinionManager::actorInput()
{
	auto game = getGame().lock();
}

void MinionManager::createMinion()
{
	if (mDelay <= 0.0f)
	{
		mDelay += 1.0f;

	/*	auto Sound = getGame().lock()->getSound();
		auto distVec = Sound->getListener() - getPosition();
		Sound->playDist(static_cast<int>(Sound::effectName::createminion), static_cast<int>(Sound::TypeChannel::minioneffect), distVec.Length());*/

		auto map = mGameMap.lock();
		auto minion = std::make_shared<DefaultMinion>(getScene(), mInfo, std::dynamic_pointer_cast<MinionManager>(weak_from_this().lock()));
		minion->setScale(1.5f);
		minion->setPosition(map->getStartPosition() + Vector3::UnitY * 50.0f);
		minion->initailize();

		mCreateMinionNum--;
		mLiveMinionNum++;

		resetHUD();
	}
}

void MinionManager::resetHUD()
{
	auto gameScene = std::dynamic_pointer_cast<GameScene>(getScene().lock());
	gameScene->getGameHUD()->resetInfo();
}