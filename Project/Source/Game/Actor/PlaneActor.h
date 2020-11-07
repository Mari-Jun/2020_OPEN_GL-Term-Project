#pragma once
#include "Actor.h"

class PlaneActor : public Actor
{
public:
	PlaneActor(const std::weak_ptr<class Game>& game);
	virtual ~PlaneActor() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void setPlaneColor(const Vector3& color);

	std::shared_ptr<class BoxComponent>& getBox() { return mBoxComponent; }
private:
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class BoxComponent> mBoxComponent;
};