#pragma once
#include "Tile.h"

class LightTile : public Tile
{
public:
	LightTile(const std::weak_ptr<class Scene>& scene, Type type = Type::Light);
	virtual ~LightTile() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;

private:
	std::shared_ptr<class Actor> mLight;

private:
	void turnOnLight();
	void turnOffLight();
};