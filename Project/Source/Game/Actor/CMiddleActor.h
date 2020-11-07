#pragma once
#include "Actor.h"

class CMiddleActor : public Actor
{
public:
	CMiddleActor(const std::weak_ptr<class Game>& game);
	virtual ~CMiddleActor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::shared_ptr<class ArmActor> mLeftArm;
	std::shared_ptr<class ArmActor> mRightArm;
};