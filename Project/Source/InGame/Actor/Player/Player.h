#pragma once
#include "../../../Game/Actor/Actor.h"
#include "../../Info/GameInfo.h"

class Player : public Actor
{
public:

	Player(const std::weak_ptr<class Scene>& scene, PlayerInfo info);
	virtual ~Player() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

protected:
	PlayerInfo mPlayerInfo;
	std::shared_ptr<class MeshComponent> mMeshComponent;

	std::shared_ptr<class RobotHead> mHead;
	std::shared_ptr<class RobotArm> mLeftArm;
	std::shared_ptr<class RobotArm> mRightArm;
	std::shared_ptr<class RobotLeg> mLeftLeg;
	std::shared_ptr<class RobotLeg> mRightLeg;

private:
	void updateBody();

public:
	PlayerInfo::PlayerType getPlayerType() const { return mPlayerInfo.getPlayerInfoType(); }
	void setPlayerInfo(const PlayerInfo& info) { mPlayerInfo = info; }
	void setPlayerTexture();
	void changePlayerTexture();
};