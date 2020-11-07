#pragma once
#include "../Component/Component.h"

class CameraComponent : public Component
{
public:
	CameraComponent(const std::weak_ptr<class Actor>& owner, int updateOrder = 300);
	virtual ~CameraComponent();

	virtual void initailize() override;
	virtual void update(float deltatime) override;

protected:
	void setViewMatrix(const Matrix4& view);
};
