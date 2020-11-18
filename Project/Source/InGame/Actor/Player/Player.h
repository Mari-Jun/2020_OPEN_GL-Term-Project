#pragma once
#include "../../../Game/Actor/Actor.h"

class Player : public Actor
{
public:
	Player(const std::weak_ptr<class Scene>& scene);
	virtual ~Player() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void updateGravity(float deltatime);

	void collides(const std::weak_ptr<class BoxComponent>& bComp);

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class BoxComponent> mBoxComponent;
	float mMoveSpeed;
	float mGravitySpeed;

protected:
	std::shared_ptr<class MoveComponent> mMoveComponent;

private:
	std::shared_ptr<class RobotHead> mHead;
	std::shared_ptr<class RobotArm> mLeftArm;
	std::shared_ptr<class RobotArm> mRightArm;
	std::shared_ptr<class RobotLeg> mLeftLeg;
	std::shared_ptr<class RobotLeg> mRightLeg;

public:
	float getMoveSpeed() const { return mMoveSpeed; }
	void setMoveSpeed(float speed) { mMoveSpeed = speed; }
	float getGravitySpeed() const { return mGravitySpeed; }
	void setGravitySpeed(float speed) { mGravitySpeed = speed; }
};