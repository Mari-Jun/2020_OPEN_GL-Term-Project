#pragma once
#include "Tile.h"

class EnemyTile : public Tile
{
public:
	EnemyTile(const std::weak_ptr<class Game>& game, Type type = Type::Tower_Ballista);
	virtual ~EnemyTile() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class EnemyTower> mEnemy;
};