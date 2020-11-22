#pragma once
#include "../Player.h"

class DefaultMinion : public Player
{
public:
	DefaultMinion(const std::weak_ptr<class Scene>& scene);
	virtual ~DefaultMinion() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class Actor> mHealthBar;
};