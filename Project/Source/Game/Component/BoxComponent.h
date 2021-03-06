#pragma once
#include "Component.h"
#include "../Physics/Coliision/Collision.h"
#include "../Physics/PhysicsEngine.h"

class BoxComponent : public Component
{
public:
	enum class OwnerType
	{
		Player,
		Enemy,
		Object,
		Etc,
		None
	};

	BoxComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class PhysEngine> engine, int updateOrder = 100);
	virtual ~BoxComponent();

	virtual void initailize() override;

	virtual void updateWorldTransForm() override;

	OwnerType getOwnerType() const { return mType; }
	std::string getOwnerTypeToString() const { return getOwnerTypeToString(mType); }
	std::string getOwnerTypeToString(OwnerType type) const;
	void setType(const std::string& type);

	void setObjectBox(const AABB& box) { mObjectBox = box; }
	const AABB& getWorldBox() const { return mWorldBox; }

	void setRotate(bool rot) { mIsRotate = rot; }

	void updateObjectBox(const Vector3& pos);

private:
	std::weak_ptr<class PhysEngine> mEngine;
	OwnerType mType;
	AABB mObjectBox;
	AABB mWorldBox;
	bool mIsRotate;
};
