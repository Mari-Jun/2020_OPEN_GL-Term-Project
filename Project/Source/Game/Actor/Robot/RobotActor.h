#pragma once
#include "../Actor.h"

class RobotActor : public Actor
{
public:
	enum class RobotState
	{
		Control,
		Running,
		Pole,
		Press
	};

	RobotActor(const std::weak_ptr<class Game>& game, RobotState state);
	virtual ~RobotActor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void collides(const std::weak_ptr<class BoxComponent>& bComp);

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::shared_ptr<class BoxComponent> mBoxComponent;

	float mGravitySpeed;
	bool mAnimation;
	RobotState mState;

private:
	std::shared_ptr<class RobotHead> mHead;
	std::shared_ptr<class RobotArm> mLeftArm;
	std::shared_ptr<class RobotArm> mRightArm;
	std::shared_ptr<class RobotArm> mLeftLeg;
	std::shared_ptr<class RobotArm> mRightLeg;

public:
	std::shared_ptr<class RobotArm> getLeftArm() { return mLeftArm; }
	std::shared_ptr<class RobotArm> getRightArm() { return mRightArm; }
	RobotState getState() { return mState; }
};