#pragma once
#include "../Player.h"

class ControlPlayer : public Player
{
public:
	ControlPlayer(const std::weak_ptr<class Scene>& scene, PlayerInfo info);
	virtual ~ControlPlayer() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void setStat(PlayerInfo info) override;
};