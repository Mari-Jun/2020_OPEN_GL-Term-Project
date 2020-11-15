#pragma once
#include "EnemyTower.h"	

class Blaster : public EnemyTower
{
public:
	Blaster(const std::weak_ptr<class Game>& game);
	virtual ~Blaster() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:

};