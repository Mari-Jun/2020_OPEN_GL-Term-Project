#pragma once
#include "../Weapon.h"	

class Cannon : public Weapon
{
public:
	Cannon(const std::weak_ptr<class Scene>& scene);
	virtual ~Cannon() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void attack();
	virtual void attackMotion();
};