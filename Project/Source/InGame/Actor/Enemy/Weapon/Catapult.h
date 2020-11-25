#pragma once
#include "../Weapon.h"	

class Catapult : public Weapon
{
public:
	Catapult(const std::weak_ptr<class Scene>& scene);
	virtual ~Catapult() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void attack();
	virtual void attackMotion();

private:
	std::shared_ptr<class Rock> mRock;
	float moveY = 0.0;
	float moveX = 0.0;
	float moveZ = 0.0;
	float mRockScaleTime = 1;
	Vector3 forVec;
public:
	void reload();
	void resetRock();
	void initRock();
	void initRock(Vector3);
	void fire();

};