#pragma once
#include "../MovePlayer.h"

class ControlPlayer : public MovePlayer
{
public:
	ControlPlayer(const std::weak_ptr<class Scene>& scene, PlayerInfo info);
	virtual ~ControlPlayer() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	virtual void setStat(PlayerInfo info) override;
};