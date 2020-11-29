#pragma once
#include "../Weapon.h"	

class Ballista : public Weapon
{
public:
	Ballista(const std::weak_ptr<class Scene>& scene);
	virtual ~Ballista() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void attack();
	virtual void attackMotion();
	virtual void setEffectIndex(int index);

private:
	int mEffectindex = 0;
};