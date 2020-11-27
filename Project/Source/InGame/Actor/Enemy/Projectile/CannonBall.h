#pragma once
#include "Projectile.h"
#include "../../../../Game/Physics/Coliision/Collision.h"

class CannonBall : public Projectile
{
public:
	CannonBall(const std::weak_ptr<class Scene>& scene);
	virtual ~CannonBall() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void collide() override;

private:
	Sphere mSphere;
};