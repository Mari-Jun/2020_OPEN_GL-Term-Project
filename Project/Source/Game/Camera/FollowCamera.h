#pragma once
#include "CameraComponent.h"

//3인칭 카메라
//보통 게임에서의 3인칭 카메라

class FollowCamera : public CameraComponent
{
public:
	FollowCamera(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Actor>& follower);
	virtual ~FollowCamera();

	virtual void initailize() override;
	virtual void update(float deltatime) override;

	void SnapToIdeal();

	float getPitchSpeed() const { return mPitchSpeed; }
	float getYawSpeed() const { return mYawSpeed; }

	void setHDist(float dist) { mHDist = dist; }
	void setVDist(float dist) { mVDist = dist; }
	void setTargetDist(float dist) { mTargetDist = dist; }
	void setPitchSpeed(float speed) { mPitchSpeed = speed; }
	void setYawSpeed(float speed) { mYawSpeed = speed; }

private:
	Vector3 updateCameraPos();

	std::weak_ptr<class Actor> mFollower;

	float mHDist;
	float mVDist;
	float mTargetDist;
	
	float mPitchSpeed;
	float mYawSpeed;
	float mMaxPitch;
	float mPitch;
};
