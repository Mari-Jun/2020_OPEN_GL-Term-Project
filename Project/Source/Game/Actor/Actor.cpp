#include "Actor.h"
#include "..\Game.h"
#include "..\Component\Component.h"

Actor::Actor(const wptrGame& Game)
	: mState(State::Active)
	, mPosition(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mGame(Game)
	, mRechangeWorldTransform(true)
{
	
}

Actor::~Actor()
{
	while (!mComponent.empty())
	{
		mComponent.clear();
	}
	mGame.lock()->removeActor(weak_from_this());
}

void Actor::initailize()
{
	mGame.lock()->addActor(shared_from_this());
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
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		//Change Component World
		for (auto comp : mComponent)
		{
			comp->updateWorldTransForm();
		}
	}
}

void Actor::rotateToNewForward(const Vector3& forward)
{
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);

	//���� ������ +X���
	if (dot > 0.9999f)
	{
		setRotation(Quaternion::Identity);
	}
	else if (dot < -0.9999f)
	{
		setRotation(Quaternion(Vector3::UnitY, Math::Pi));
	}
	else
	{
		//������ ���� ���� ���� �������� ȸ��
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
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