#pragma once
#include "Tile.h"

class OrnamentTile : public Tile
{
public:
	OrnamentTile(const std::weak_ptr<class Scene>& scene, TileType type);
	virtual ~OrnamentTile() noexcept;

	virtual void initailize() override;

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;

private:
	void setOrnament();
};