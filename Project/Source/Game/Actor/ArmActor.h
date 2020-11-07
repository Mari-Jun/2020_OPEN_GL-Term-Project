#pragma once
#include "Actor.h"

class ArmActor : public Actor
{
public:
	ArmActor(const std::weak_ptr<class Game>& game, bool left);
	virtual ~ArmActor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	bool mLeft;
	float mRad;
	int rotPlus;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;
};