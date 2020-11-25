#pragma once
#include "Projectile.h"
#include "../../../../Game/Physics/Coliision/Collision.h"

class Rock : public Projectile
{
public:
	Rock(const std::weak_ptr<class Scene>& scene);
	virtual ~Rock() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void collide() override;

private:
	LineSegment mLine;
	float forwardSpeed = 100.0f;
	float upSpeed = -100.0f;
	bool flag = false;	//false면 초기상태, true면 발사 상태 (움직인단 소리) 
	bool split = false;	//false면 큰 상태, true면 쪼개진 상태 (더이상 안쪼개짐)

public:
	void setforwardSpeed(float Speed) { forwardSpeed = Speed; }
	float getforwardSpeed() const { return forwardSpeed; }
	void setupSpeed(float Speed) { upSpeed = Speed; }
	float getupSpeed() const { return upSpeed; }
	void setflag(bool Flag) { flag = Flag; }
	bool getflag() const{ return flag; }

private:
	void gravity(float deltatime);
};