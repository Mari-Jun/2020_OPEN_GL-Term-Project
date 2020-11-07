#pragma once
#include "../../Actor.h"

class Snow : public Actor
{
public:
	Snow(const std::weak_ptr<class Game>& game);
	virtual ~Snow() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class DefualtShape> mSnow;
	std::shared_ptr<class MoveComponent> mMoveComponent;
};