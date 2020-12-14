#pragma once
#include "OrnamentTile.h"

class EnemyTile : public OrnamentTile
{
public:
	EnemyTile(const std::weak_ptr<class Scene>& scene, TileType type = TileType::Tower_Ballista);
	virtual ~EnemyTile() noexcept;

	virtual void initailize() override;

private:
	std::shared_ptr<class EnemyTower> mEnemy;
};