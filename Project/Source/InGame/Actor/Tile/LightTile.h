#pragma once
#include "Tile.h"

class LightTile : public Tile
{
public:
	LightTile(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Light>& light, const std::string& time);
	virtual ~LightTile() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;

private:
	std::weak_ptr<class Light> mLight;
	std::shared_ptr<class Actor> mLightActor;
	std::shared_ptr<struct PointLight> mPointLight;
	std::string mTime;

private:
	void turnOnLight();
	void turnOffLight();
};