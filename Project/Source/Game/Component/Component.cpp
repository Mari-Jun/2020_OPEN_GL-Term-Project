#include "Component.h"
#include "../Actor\Actor.h"
#include <iostream>

Component::Component(const std::weak_ptr<class Actor>& owner, int updateOrder)
	: mOwner(owner)
	, mUpdateOrder(updateOrder)
{
	std::cerr << "Create Component\n";
}

Component::~Component()
{
	if (!mOwner.expired())
	{
		mOwner.lock()->removeComponent(weak_from_this());
	}
	std::cerr << "Destory Component\n";
}

void Component::initailize()
{
	mOwner.lock()->addComponent(shared_from_this());
}

void Component::update(float deltatime)
{

}