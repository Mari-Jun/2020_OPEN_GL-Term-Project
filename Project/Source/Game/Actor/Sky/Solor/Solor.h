#pragma once
#include "../../Actor.h"

class Solor : public Actor
{
public:
	Solor(const std::weak_ptr<class Game>& game);
	virtual ~Solor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::vector<std::shared_ptr<class  DefualtShape>> mPlanets;
};