#pragma once
#include "Tile.h"
#include "../../../Game/Physics/Coliision/Collision.h"

class EndPointTile : public Tile
{
public:
	EndPointTile(const std::weak_ptr<class Scene>& scene);
	virtual ~EndPointTile() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;

	void collidePlayers();
};