#pragma once
#include "../Actor.h"

class RobotHead : public Actor
{
public:
	RobotHead(const std::weak_ptr<class Game>& game);
	virtual ~RobotHead() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void setMeshColor(const Vector3& color) { mMeshColor = color; }

	void createNose();

private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	Vector3 mMeshColor;
	
	std::shared_ptr<class RobotHead> mNose;
};