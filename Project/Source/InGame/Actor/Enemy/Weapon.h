#pragma once
#include "../../../Game/Actor/Actor.h"

class Weapon : public Actor
{
public:
	Weapon(const std::weak_ptr<class Scene>& scene);
	virtual ~Weapon() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void attack();
	virtual void attackMotion();
	virtual void setEffectIndex(int index);

private:
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::weak_ptr<class Actor> mTarget;
	float mAttackDelay;
	float mCurDelay;
	float mAttackRange;

public:
	const std::weak_ptr<class Actor>& getTarget() const { return mTarget; }
	void setTarget(const std::weak_ptr<class Actor> target) { mTarget = target; }
	float getAttackDelay() const { return mAttackDelay; }
	float getCurDelay() const { return mCurDelay; }
	float getAttackRange() const { return mAttackRange; }
	void setAttackDelay(float delay) { mAttackDelay = delay; }
	void setCurDelay(float delay) { mCurDelay = delay; }
};