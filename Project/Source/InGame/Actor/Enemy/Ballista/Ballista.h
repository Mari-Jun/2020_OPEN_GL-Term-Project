#pragma once
#include "../EnemyTower.h"	

class Ballista : public EnemyTower
{
public:
	Ballista(const std::weak_ptr<class Scene>& scene);
	virtual ~Ballista() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class Bow> mBow;
};