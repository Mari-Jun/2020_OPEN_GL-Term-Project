#pragma once
#include "../../../../Game/Actor/Actor.h"

class Projectile : public Actor
{
public:
	enum class PjtType
	{
		Arrow,
		CannonBall,
		Rock,
		Laser
	};

	Projectile(const std::weak_ptr<class Scene>& scene, PjtType type = PjtType::Arrow);
	virtual ~Projectile() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void collide();

private:
	PjtType mType;

protected:
	std::shared_ptr<class Mesh> loadMesh() const;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class MoveComponent> mMoveComponent;

public:
	PjtType getPjtType() const { return mType; }
	std::string getPjtTypeToString() const;
};