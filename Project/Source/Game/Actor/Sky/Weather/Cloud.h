#pragma once
#include "../../Actor.h"

class Cloud : public Actor
{
public:
	Cloud(const std::weak_ptr<class Game>& game);
	virtual ~Cloud() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class MoveComponent> mMoveComponent;
	bool mSnowing;
};