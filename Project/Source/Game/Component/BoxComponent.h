#pragma once
#include "Component.h"
#include "../Physics/Coliision/Collision.h"
#include "../Physics/PhysicsEngine.h"

class BoxComponent : public Component
{
public:
	BoxComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class PhysEngine> engine, int updateOrder = 100);
	virtual ~BoxComponent();

	virtual void initailize() override;

	virtual void updateWorldTransForm() override;

	void setObjectBox(const AABB& box) { mObjectBox = box; }
	const AABB& getWorldBox() const { return mWorldBox; }

	void setRotate(bool rot) { mIsRotate = rot; }

	void updateObjectBox(const Vector3& pos);

private:
	std::weak_ptr<class PhysEngine> mEngine;
	AABB mObjectBox;
	AABB mWorldBox;
	bool mIsRotate;
};
