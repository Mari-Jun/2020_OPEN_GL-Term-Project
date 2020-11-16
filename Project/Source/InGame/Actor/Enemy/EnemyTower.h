#pragma once
#include "../../../Game/Actor/Actor.h"

class EnemyTower : public Actor
{
public:
	enum class Type
	{
		Ballista, Ballista_Bow,
		Blaster,
		Cannon,
		Catapult
	};

	EnemyTower(const std::weak_ptr<class Scene>& scene, Type type = Type::Ballista);
	virtual ~EnemyTower() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

private:
	std::shared_ptr<class Mesh> loadMesh() const;
	void findPlayer();
	void chasePlayer();	

private:
	Type mType;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::weak_ptr<class Actor> mTarget;
	float mAttackRange;

public:
	Type getType() const { return mType; }
	std::string getTypeToString() const;
	const std::weak_ptr<class Actor>& getTarget() const { return mTarget; }
	float getAttackRange() const { return mAttackRange; }
	void setAttackRange(float range) { mAttackRange = range; }
};