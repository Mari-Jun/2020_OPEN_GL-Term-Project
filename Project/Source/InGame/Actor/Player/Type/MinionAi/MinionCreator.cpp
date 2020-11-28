#include "MinionCreator.h"
#include "MinionAi.h"
#include "../../../../../Game/Game.h"
#include "../../../../../Game/Input/KeyBoard.h"
#include "../../../../Map/GameMap.h"
#include "../DefaultMinion.h"

MinionCreator::MinionCreator(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class GameMap>& gameMap, const PlayerInfo& info)
	: Actor(scene)
	, mGameMap(gameMap)
	, mInfo(info)
{

}

MinionCreator::~MinionCreator()
{

}

void MinionCreator::initailize()
{
	Actor::initailize();

	mMinionAi = std::make_shared<MinionAi>(getScene());
	auto map = mGameMap.lock();
	mMinionAi->initailize(map->getTiles(), map->getStartPosIndex(), map->getEndPosIndex(), map->getTileSize(), map->getMapSize());

	auto minion = std::make_shared<DefaultMinion>(getScene(), mInfo, mMinionAi);
	minion->setScale(1.5f);
	minion->setPosition(map->getStartPosition() + Vector3(-10.0f, 100.0f, 10.0f));
	minion->initailize();
}

void MinionCreator::updateActor(float deltatime)
{
	
}

void MinionCreator::actorInput()
{
	auto game = getGame().lock();
}