#pragma once
#include "../Weapon.h"	

class Blaster : public Weapon
{
public:
	Blaster(const std::weak_ptr<class Scene>& scene);
	virtual ~Blaster() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void attack();
	virtual void attackMotion();
};