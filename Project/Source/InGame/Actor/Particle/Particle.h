#pragma once
#include "../../../Game/Actor/Actor.h"

class Particle : public Actor
{
public:
	Particle(const std::weak_ptr<class Scene>& scene, const std::string& season);
	virtual ~Particle() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class BillBoardComponent> mParticle;
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::string mSeason;
};