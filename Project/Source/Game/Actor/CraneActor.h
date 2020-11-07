#pragma once
#include "Actor.h"

class CraneActor : public Actor
{
public:
	CraneActor(const std::weak_ptr<class Game>& game);
	virtual ~CraneActor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::shared_ptr<class CMiddleActor> mMiddleActor;
};