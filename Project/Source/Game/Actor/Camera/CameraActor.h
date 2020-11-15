#pragma once
#include "../Actor.h"

class CameraActor : public Actor
{
public:
	enum class CameraState
	{
		Basic,
		Mouse,
	};

	CameraActor(const std::weak_ptr<class Scene>& scene);
	virtual ~CameraActor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void InputBasic();
	void InputMouse();

private:
	CameraState mState;
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::shared_ptr<class FPSMouseCamera> mFPSCamera;
};