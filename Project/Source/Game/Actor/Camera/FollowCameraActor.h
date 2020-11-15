#pragma once
#include "../Actor.h"

class FollowCameraActor : public Actor
{
public:
	FollowCameraActor(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Actor>& follower);
	virtual ~FollowCameraActor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::weak_ptr<class Actor> mFollower;
	std::shared_ptr<class FollowCamera> mFollowCamera;
	std::shared_ptr<class BoxComponent> mBoxComponent;
};