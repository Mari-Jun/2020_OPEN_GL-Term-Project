#pragma once
#include "../../../Game/Actor/Actor.h"

class Snow : public Actor
{
public:
	Snow(const std::weak_ptr<class Scene>& scene);
	virtual ~Snow() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class BillBoardComponent> mSnow;
	std::shared_ptr<class MoveComponent> mMoveComponent;
};