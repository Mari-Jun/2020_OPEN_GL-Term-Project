#pragma once
#pragma once
#include "../Actor.h"

class Building : public Actor
{
public:
	Building(const std::weak_ptr<class Game>& game);
	virtual ~Building() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:

};