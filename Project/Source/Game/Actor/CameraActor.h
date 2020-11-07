#pragma once
#include "Actor.h"

class CameraActor : public Actor
{
public:
	enum class CameraState
	{
		Basic,
		Mouse,
		Follow
	};

	CameraActor(const std::weak_ptr<class Game>& game);
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