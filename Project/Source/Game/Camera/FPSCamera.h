#pragma once
#include "CameraComponent.h"

//1인칭 카메라
//마우스 미사용 카메라

class FPSCamera : public CameraComponent
{
public:
	FPSCamera(const std::weak_ptr<class Actor>& owner);
	virtual ~FPSCamera();

	virtual void initailize() override;
	virtual void update(float deltatime) override;
private:

};
