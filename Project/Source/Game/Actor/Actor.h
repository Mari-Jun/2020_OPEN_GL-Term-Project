#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../Math/Math.h"
#include "../Scene/Scene.h"

class Actor : public std::enable_shared_from_this<Actor>
{
public:
	enum class State
	{
		Active,
		Paused,
		Dead
	};
	enum class Type
	{
		Player,
		Enemy,
		Object,
		Particle,
		Ui,
		Etc
	};

	Actor(const std::weak_ptr<class Scene>& scene, Type type = Type::Object);
	virtual ~Actor() noexcept;

	virtual void initailize();

private:
	State mState;
	Type mType;

	Matrix4 mWorldTransform;
	Vector3 mPosition;
	Quaternion mRotation;
	Vector3 mScale;
	bool mRechangeWorldTransform;

	std::vector<std::shared_ptr<class Component>> mComponent;
	std::weak_ptr<class Scene> mScene;

public:
	void update(float deltatime);
	void updateCompont(float deltatime);
	virtual void updateActor(float deltatime);	

	void processInput();
	virtual void actorInput();
	
	State getState() const { return mState; }
	void setState(State state) { mState = state; }
	std::string getTypeToString() const { return getTypeToString(mType); }
	std::string getTypeToString(Type type) const;

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

	const std::weak_ptr<class Scene>& getScene() const { return mScene; }
	std::weak_ptr<class Scene>& getScene() { return const_cast<std::weak_ptr<class Scene>&>(std::as_const(*this).getScene()); }
	const std::weak_ptr<class Game>& getGame() const { return getScene().lock()->getGame(); }
	std::weak_ptr<class Game>& getGame() { return const_cast<std::weak_ptr<class Game>&>(std::as_const(*this).getGame()); }

	void addComponent(const std::shared_ptr<class Component>& component);
	void removeComponent(const std::weak_ptr<class Component>& component);

};