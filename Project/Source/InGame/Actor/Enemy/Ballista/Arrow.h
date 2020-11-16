#pragma once
#include "../../../../Game/Actor/Actor.h"

class Arrow : public Actor
{
public:
	Arrow(const std::weak_ptr<class Scene>& scene);
	virtual ~Arrow() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;
};