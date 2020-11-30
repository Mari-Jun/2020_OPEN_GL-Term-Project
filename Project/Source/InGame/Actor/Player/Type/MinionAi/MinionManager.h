#pragma once
#include "../../../../Info/GameInfo.h"
#include "../../../../../Game/Actor/Actor.h"

class MinionManager : public Actor
{
public:
	MinionManager(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class GameMap>& gameMap, const PlayerInfo& info);
	virtual ~MinionManager() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::weak_ptr<class GameMap> mGameMap;
	std::shared_ptr<class MinionAi> mMinionAi;
	PlayerInfo mInfo;
	float mDelay;
	int mCreateMinionNum;
	int mLiveMinionNum;
	int mClearMinionNum;

private:
	void createMinion();

public:
	const std::shared_ptr<class MinionAi>& getMinionAi() const { return mMinionAi; }
	int getCreateMinion() const { return mCreateMinionNum; }
	int getLiveMinion() const { return mLiveMinionNum; }
	int getClearMinion() const { return mClearMinionNum; }
	void setLiveMinion(int num) { mLiveMinionNum = num; }
	void setClearMinion(int num) { mClearMinionNum = num; }

	void resetHUD();
};