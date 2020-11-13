#pragma once
#include "../../../Game/Actor/Actor.h"

class ParticleCreater : public Actor
{
public:
	ParticleCreater(const std::weak_ptr<class Game>& game);
	virtual ~ParticleCreater() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	bool mSnowing;
};