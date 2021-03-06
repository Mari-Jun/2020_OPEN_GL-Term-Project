#pragma once
#include "../../../../Game/Actor/Actor.h"

class RobotLeg : public Actor
{
public:
	RobotLeg(const std::weak_ptr<class Scene>& scene, bool left);
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

public:
	void setPlayerTexture(const std::string& fileName, int index);
	void resetTexture();
};