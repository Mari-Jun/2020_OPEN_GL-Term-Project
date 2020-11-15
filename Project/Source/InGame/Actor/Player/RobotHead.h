#pragma once
#include "../../../Game/Actor/Actor.h"

class RobotHead : public Actor
{
public:
	RobotHead(const std::weak_ptr<class Scene>& scene);
	virtual ~RobotHead() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;	
	std::shared_ptr<class BoxComponent> mBoxComponent;
};