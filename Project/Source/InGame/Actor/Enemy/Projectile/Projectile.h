#pragma once
#include "../../../../Game/Actor/Actor.h"

class Projectile : public Actor
{
public:
	enum class Type
	{
		Arrow,
		CannonBall,
		Rock,
		Raser
	};

	Projectile(const std::weak_ptr<class Scene>& scene, Type type = Type::Arrow);
	virtual ~Projectile() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void collide();

private:
	Type mType;

protected:
	std::shared_ptr<class Mesh> loadMesh() const;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;

public:
	Type getType() const { return mType; }
	std::string getTypeToString() const;
};