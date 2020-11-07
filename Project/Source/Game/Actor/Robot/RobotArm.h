#pragma once
#include "../Actor.h"

class RobotArm : public Actor
{
public:
	RobotArm(const std::weak_ptr<class Game>& game, bool front);
	virtual ~RobotArm() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void setMeshColor(const Vector3& color) { mMeshColor = color; }
	void setMove(bool move) { mMove = move; }
	void setRot(float rot) { mRot = rot; }

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	Vector3 mMeshColor;
	bool mFront;
	bool mMove;
	float mRot;
};