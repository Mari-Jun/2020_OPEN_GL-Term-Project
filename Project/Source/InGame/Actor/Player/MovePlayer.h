//무브플레이어.h
#pragma once
#include "Player.h"


struct PlayerStat
{
	float mHp;
	float mMaxHp;
	float mDef;
	float mSpeed;
};

class MovePlayer : public Player
{
public:

	MovePlayer(const std::weak_ptr<class Scene>& scene, PlayerInfo info);
	virtual ~MovePlayer() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void collides(const std::weak_ptr<class BoxComponent>& bComp);
	void updateAnimation();

private:
	std::shared_ptr<class BoxComponent> mBoxComponent;
	std::shared_ptr<class Actor> mHealthBar;
	float mGravitySpeed;

private:
	void updateGravity(float deltatime);
	virtual void setStat(PlayerInfo info);
	virtual void checkHp();

protected:
	PlayerStat mStat;
	std::shared_ptr<class MoveComponent> mMoveComponent;
	std::shared_ptr<class GameMinimap> mMarker;

public:
	float getGravitySpeed() const { return mGravitySpeed; }
	void setGravitySpeed(float speed) { mGravitySpeed = speed; }

	void decreaseHp(float damage);
	void increaseHp(float hill);
};