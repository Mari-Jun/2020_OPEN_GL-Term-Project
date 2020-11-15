#pragma once
#include "../../../../Game/Actor/Actor.h"

class EnemyTower : public Actor
{
public:
	enum class Type
	{
		Ballista,
		Blaster,
		Cannon,
		Catapult
	};

	EnemyTower(const std::weak_ptr<class Game>& game, Type type = Type::Ballista);
	virtual ~EnemyTower() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	std::shared_ptr<class Mesh> loadMesh() const;

private:
	Type mType;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;

public:
	Type getType() const { return mType; }
	std::string getTypeToString() const;
};