#pragma once
#include "CameraComponent.h"

//1인칭 카메라
//마우스 미사용 카메라

class FPSMouseCamera : public CameraComponent
{
public:
	FPSMouseCamera(const std::weak_ptr<class Actor>& owner);
	virtual ~FPSMouseCamera();

	virtual void initailize() override;
	virtual void update(float deltatime) override;

	float getPitchSpeed() const { return mPitchSpeed; }
	float getPitchMaxSpeed() const { return mPitchMaxSpeed; }
	float getPitch() const { return mPitch; }

	void setPitchSpeed(float speed) { mPitchSpeed = speed; }
	void setPitchMaxSpeed(float speed) { mPitchMaxSpeed = speed; }

private:
	float mPitchSpeed;
	float mPitchMaxSpeed;
	float mPitch;
};
