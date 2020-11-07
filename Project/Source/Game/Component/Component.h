#pragma once
#include <memory>
#include "../Math/Math.h"

class Component : public std::enable_shared_from_this<Component>
{
public:
	Component(const std::weak_ptr<class Actor>& owner, int updateOrder = 100);
	virtual ~Component() noexcept;

	virtual void initailize();

	virtual void draw(std::unique_ptr<class Shader>& shader) {}
	virtual void update(float deltatime);

	virtual void updateWorldTransForm() {} 

	std::weak_ptr<class Actor>& getOwner() { return mOwner; }

protected:
	std::weak_ptr<class Actor> mOwner;
	int mUpdateOrder;

public:
	int getUpdateOrder() const { return mUpdateOrder; }
};
