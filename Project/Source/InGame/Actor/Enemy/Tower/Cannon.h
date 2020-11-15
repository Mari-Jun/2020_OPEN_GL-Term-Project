#pragma once
#include "EnemyTower.h"	

class Cannon : public EnemyTower
{
public:
	Cannon(const std::weak_ptr<class Game>& game);
	virtual ~Cannon() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:

};