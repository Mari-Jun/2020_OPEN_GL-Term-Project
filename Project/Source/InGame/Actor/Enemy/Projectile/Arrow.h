#pragma once
#include "Projectile.h"
#include "../../../../Game/Physics/Coliision/Collision.h"

class Arrow : public Projectile
{
public:
	Arrow(const std::weak_ptr<class Scene>& scene);
	virtual ~Arrow() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;
	
	virtual void collide() override;

private:
	LineSegment mLine;
};