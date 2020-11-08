#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../Math/Math.h"

class Actor : public std::enable_shared_from_this<Actor>
{
public:
	using wptrGame = std::weak_ptr<class Game>;
	enum class State
	{
		Active,
		Paused,
		Dead
	};

	Actor(const wptrGame& Game);
	virtual ~Actor() noexcept;

	virtual void initailize();

private:
	State mState;

	Matrix4 mWorldTransform;
	Vector3 mPosition;
	Quaternion mRotation;
	Vector3 mScale;
	bool mRechangeWorldTransform;

	std::vector<std::shared_ptr<class Component>> mComponent;
	wptrGame mGame;

public:
	void update(float deltatime);
	void updateCompont(float deltatime);
	virtual void updateActor(float deltatime);	

	void processInput();
	virtual void actorInput();
	
	State getState() const { return mState; }
	void setState(State state) { mState = state; }

	void updateWorldTransform();
	void rotateToNewForward(const Vector3& forward);
	const Matrix4 getWorldTransform() const { return mWorldTransform; }

	const Vector3& getPosition() const { return mPosition; }
	void setPosition(const Vector3& pos) { mPosition = pos; mRechangeWorldTransform = true; }
	const Quaternion& getRotation() const { return mRotation; }
	void setRotation(const Quaternion& rotation) { mRotation = rotation; mRechangeWorldTransform = true; }
	const Vector3& getScale() const { return mScale; }
	void setScale(float scale) { mScale *= scale; mRechangeWorldTransform = true; }
	void setScale(const Vector3& scale) { mScale = scale; mRechangeWorldTransform = true; }

	Vector3 getForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }
	Vector3 getSide() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	Vector3 getUp() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	const wptrGame& getGame() const { return mGame; }
	wptrGame& getGame() { return const_cast<wptrGame&>(std::as_const(*this).getGame()); }

	void addComponent(const std::shared_ptr<class Component>& component);
	void removeComponent(const std::weak_ptr<class Component>& component);

};