#pragma once
#include "CameraComponent.h"

//1��Ī ī�޶�
//���콺 �̻�� ī�޶�

class FPSCamera : public CameraComponent
{
public:
	FPSCamera(const std::weak_ptr<class Actor>& owner);
	virtual ~FPSCamera();

	virtual void initailize() override;
	virtual void update(float deltatime) override;
private:

};
