#pragma once
#include "../EnemyTower.h"	

class Bow: public EnemyTower
{
public:
	Bow(const std::weak_ptr<class Scene>& scene);
	virtual ~Bow() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	float mAttackDelay;
};