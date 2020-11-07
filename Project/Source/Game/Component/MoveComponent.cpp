#include "MoveComponent.h"
#include "../Actor/Actor.h"
#include <iostream>

MoveComponent::MoveComponent(const std::weak_ptr<Actor>& actor, int updateOrder)
	: Component(actor, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
	, mSideSpeed(0.0f)
	, mUpSpeed(0.0f)
{
	std::cerr << "Create MoveComponent\n";
}

MoveComponent::~MoveComponent()
{
	std::cerr << "Destory MoveComponent\n";
}

void MoveComponent::update(float deltatime)
{
	//Angluar Move
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = mOwner.lock()->getRotation();
		float angle = mAngularSpeed * deltatime;
		
		Quaternion axis(Vector3::UnitY, angle);
		rot = Quaternion::Concatenate(rot, axis);
		mOwner.lock()->setRotation(rot);
	}

	//Foward Move, Side Move, Up Move
	if (!Math::NearZero(mForwardSpeed) || 
		!Math::NearZero(mSideSpeed) || 
		!Math::NearZero(mUpSpeed))
	{
		auto actor = mOwner.lock();
		Vector3 pos = actor->getPosition();
		pos += actor->getForward() * mForwardSpeed * deltatime;
		pos += actor->getSide() * mSideSpeed * deltatime;
		pos += actor->getUp() * mUpSpeed * deltatime;
		actor->setPosition(pos);
	}
}