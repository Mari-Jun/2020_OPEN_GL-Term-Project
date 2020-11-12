#pragma once
#include "../Actor.h"

class RobotLeg : public Actor
{
public:
	RobotLeg(const std::weak_ptr<class Game>& game, bool left);
	virtual ~RobotLeg() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void setMove(bool move) { mMove = move; }
	void setRot(float rot) { mRot = rot; }

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	bool mLeft;
	bool mMove;
	float mRot;
	float mRotSpeed;
};