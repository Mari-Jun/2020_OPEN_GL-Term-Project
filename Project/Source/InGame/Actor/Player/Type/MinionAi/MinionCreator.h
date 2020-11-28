#pragma once
#include "../../../../Info/GameInfo.h"
#include "../../../../../Game/Actor/Actor.h"

class MinionCreator : public Actor
{
public:
	MinionCreator(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class GameMap>& gameMap, const PlayerInfo& info);
	virtual ~MinionCreator() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::weak_ptr<class GameMap> mGameMap;
	std::shared_ptr<class MinionAi> mMinionAi;
	PlayerInfo mInfo;
};