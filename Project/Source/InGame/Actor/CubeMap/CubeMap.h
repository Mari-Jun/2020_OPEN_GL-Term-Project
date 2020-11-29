#pragma once
#include "../../../Game/Actor/Actor.h"

class CubeMap : public Actor
{
public:
	CubeMap(const std::weak_ptr<class Scene>& scene);
	virtual ~CubeMap() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;


private:
	std::shared_ptr<class CubeMapComponent> mCubeMap;
	std::shared_ptr<class CubeMaps> mCubeMaps;
};