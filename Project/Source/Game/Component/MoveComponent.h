#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(const std::weak_ptr<class Actor>& actor, int updateOrder = 10);
	virtual ~MoveComponent() noexcept;

	virtual void update(float deltatime) override;

	float getAugluarSpeed() const { return mAngularSpeed; }
	float getForwardSpeed() const { return mForwardSpeed; }
	float getSideSpeed() const { return mSideSpeed; }
	float getUpSpeed() const { return  mUpSpeed; }
	void setAngularSpeed(float speed) { mAngularSpeed = speed; }
	void setForwardSpeed(float speed) { mForwardSpeed = speed; }
	void setSideSpeed(float speed) { mSideSpeed = speed; }
	void setUpSpeed(float speed) { mUpSpeed = speed; }

private:
	float mAngularSpeed;
	float mForwardSpeed;
	float mSideSpeed;
	float mUpSpeed;

};