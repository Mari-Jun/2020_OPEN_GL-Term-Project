#pragma once
#include "../../../Game/Actor/Actor.h"

class ParticleCreator : public Actor
{
public:
	ParticleCreator(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Actor>& follower);
	virtual ~ParticleCreator() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::weak_ptr<class Actor> mFollower;
	bool mSnowing;
};