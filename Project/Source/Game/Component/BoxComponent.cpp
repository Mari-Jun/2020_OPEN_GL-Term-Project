#include "BoxComponent.h"
#include "../Game.h"
#include "../Actor/Actor.h"
#include <iostream>

BoxComponent::BoxComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class PhysEngine> engine, int updateOrder)
	: Component(owner, updateOrder)
	, mEngine(engine)
	, mObjectBox(Vector3::Zero, Vector3::Zero)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
	, mIsRotate(true)
{

}

BoxComponent::~BoxComponent()
{
	mEngine.lock()->removeBox(getTypeToString(), std::dynamic_pointer_cast<BoxComponent>(weak_from_this().lock()));
}

void BoxComponent::initailize()
{
	Component::initailize();
	setType(mOwner.lock()->getTypeToString());
	mEngine.lock()->addBox(getTypeToString(), std::dynamic_pointer_cast<BoxComponent>(weak_from_this().lock()));
}

void BoxComponent::updateWorldTransForm()
{
	mWorldBox = mObjectBox;

	auto actor = mOwner.lock();

	mWorldBox.mMax *= actor->getScale();
	mWorldBox.mMin *= actor->getScale();

	if (mIsRotate)
	{
		mWorldBox.Rotate(actor->getRotation());
	}

	mWorldBox.mMax += actor->getPosition();
	mWorldBox.mMin += actor->getPosition();
}

void BoxComponent::updateObjectBox(const Vector3& pos)
{
	mObjectBox.UpdateMinMax(pos);
}

void BoxComponent::setType(const std::string& type)
{
	if (type == "player")
	{
		mType = OnwerType::Player;
	}
	else if (type == "enemy")
	{
		mType = OnwerType::Enemy;
	}
	else if (type == "object")
	{
		mType = OnwerType::Object;
	}
	else if (type == "etc")
	{
		mType = OnwerType::Etc;
	}
	else
	{
		mType = OnwerType::None;
	}
}

std::string BoxComponent::getTypeToString() const
{
	switch (mType)
	{
	case BoxComponent::OnwerType::Player:
		return "player";
	case BoxComponent::OnwerType::Enemy:
		return "enemy";
	case BoxComponent::OnwerType::Object:
		return "object";
	case BoxComponent::OnwerType::Etc:
		return "etc";
	case BoxComponent::OnwerType::None:
		return "none";
	default:
		return "";
	}
}