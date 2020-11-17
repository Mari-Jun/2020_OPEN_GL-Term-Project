#include "Actor.h"
#include "..\Game.h"
#include "../Scene/Scene.h"
#include "..\Component\Component.h"

Actor::Actor(const std::weak_ptr<class Scene>& scene, Type type)
	: mState(State::Active)
	, mType(type)
	, mPosition(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mRechangeWorldTransform(true)
	, mScene(scene)
{

}

Actor::~Actor()
{
	for (auto comp : mComponent)
	{
		comp.reset();
	}
	mComponent.clear();
	if (!mScene.expired())
	{
		mScene.lock()->removeActor(getTypeToString(), weak_from_this());
	}
}

void Actor::initailize()
{
	mScene.lock()->addActor(getTypeToString(), shared_from_this());
}

void Actor::update(float deltatime)
{
	if (mState == State::Active)
	{
		updateWorldTransform();

		updateCompont(deltatime);
		updateActor(deltatime);

		updateWorldTransform();
	}
}

void Actor::updateCompont(float deltatime)
{
	for (auto component : mComponent)
	{
		component->update(deltatime);
	}
}

void Actor::updateActor(float deltatime)
{
	
}

void Actor::processInput()
{
	if (mState == State::Active)
	{
		//Component

		//Actor
		actorInput();
	}
}

void Actor::actorInput()
{

}

void Actor::updateWorldTransform()
{
	if (mRechangeWorldTransform)
	{
		//Change Actor World
		mRechangeWorldTransform = false;
		convertWorldTransform(mWorldTransform);

		//Change Component World
		for (const auto& comp : mComponent)
		{
			comp->updateWorldTransForm();
		}
	}
}

void Actor::convertWorldTransform(Matrix4& worldTransform)
{
	worldTransform = Matrix4::CreateScale(mScale);
	worldTransform *= Matrix4::CreateFromQuaternion(mRotation);
	worldTransform *= Matrix4::CreateTranslation(mPosition);
}

void Actor::rotateToNewForward(const Vector3& forward)
{
	float dot = Vector3::Dot(Vector3::UnitZ, forward);
	float angle = Math::Acos(dot);

	//진행 방향이 +Z라면
	if (dot > 0.9999f)
	{
		setRotation(Quaternion::Identity);
	}
	//진행 방향이 -Z라면
	else if (dot < -0.9999f)
	{
		setRotation(Quaternion(Vector3::UnitY, Math::Pi));
	}
	else
	{
		//외적을 통해 얻은 축을 기준으로 회전
		Vector3 axis = Vector3::Cross(Vector3::UnitZ, forward);
		axis.Normalize();
		setRotation(Quaternion(axis, angle));
	}
}

void Actor::addComponent(const std::shared_ptr<Component>& component)
{
	int order = component->getUpdateOrder();
	auto iter = mComponent.begin();
	for (; iter != mComponent.end(); ++iter)
	{
		if (order < (*iter)->getUpdateOrder())
		{
			break;
		}
	}
	mComponent.insert(iter, component);
}

void Actor::removeComponent(const std::weak_ptr<Component>& component)
{
	auto iter = std::find_if(mComponent.begin(), mComponent.end(),
		[&component](const std::weak_ptr<Component>& comp)
		{return  comp.lock() == component.lock(); });

	if (iter != mComponent.end())
	{
		mComponent.erase(iter);
	}
}

std::string Actor::getTypeToString(Type type) const
{
	switch (type)
	{
	case Actor::Type::Player:
		return "player";
	case Actor::Type::Enemy:
		return "enemy";
	case Actor::Type::Object:
		return "object";
	case Actor::Type::Particle:
		return "particle";
	case Actor::Type::Ui:
		return "ui";
	case Actor::Type::Etc:
		return "etc";
	default:
		return "";
	}
}