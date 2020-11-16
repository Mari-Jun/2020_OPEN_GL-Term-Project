#pragma once
#include "../EnemyTower.h"	

class Catapult : public EnemyTower
{
public:
	Catapult(const std::weak_ptr<class Scene>& scene);
	virtual ~Catapult() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:

};