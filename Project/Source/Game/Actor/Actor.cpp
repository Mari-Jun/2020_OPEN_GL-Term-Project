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
	rotateToNewForwardNotY(forward);

	auto y = forward;
	auto b = getForward();
	auto dot = Vector3::Dot(y, b);
	dot = Math::Clamp(dot, -1.0f, 1.0f);
	dot = Math::Acos(dot);

	if (!Math::NearZero(dot))
	{
		Vector3 axis = Vector3::Cross(y, b);
		axis.Normalize();
		setRotation(Quaternion::Concatenate(getRotation(), Quaternion(axis, -dot)));
	}
}

void Actor::rotateToNewForwardNotY(const Vector3& forward)
{
	auto a = forward;
	auto b = getForward();
	a.y = b.y = 0.0f;
	a.Normalize();
	b.Normalize();

	float dot = Vector3::Dot(a, b);
	dot = Math::Clamp(dot, -1.0f, 1.0f);
	dot = Math::Acos(dot);

	if (!Math::NearZero(dot))
	{
		if (Vector3::Cross(a, b).y > 0.0f)
			dot *= -1;

		setRotation(Quaternion::Concatenate(getRotation(), Quaternion(Vector3::UnitY, dot)));
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