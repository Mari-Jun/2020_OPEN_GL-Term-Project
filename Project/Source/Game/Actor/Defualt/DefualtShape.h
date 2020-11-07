#pragma once
#include "../Actor.h"

class DefualtShape : public Actor
{
public:
	enum class Shape
	{
		Box,
		Sphere,
		Slinder,
		Pyramid
	};

	DefualtShape(const std::weak_ptr<class Game>& game, Shape shape = Shape::Box, bool collides = true);
	virtual ~DefualtShape() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void setMeshColor(const Vector3& color) { mMeshColor = color; }

	const std::shared_ptr<class BoxComponent>& getBoxComponent() const { return mBoxComponent; }
private:
	Shape mShape;
	bool mCollides;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class BoxComponent> mBoxComponent;
	Vector3 mMeshColor;
};