#pragma once
#include "Tile.h"

class EnemyTile : public Tile
{
public:
	EnemyTile(const std::weak_ptr<class Scene>& scene, Type type = Type::Tower_Ballista);
	virtual ~EnemyTile() noexcept;

	virtual void initailize() override;

private:
	std::shared_ptr<class EnemyTower> mEnemy;
};