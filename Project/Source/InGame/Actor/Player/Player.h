#pragma once
#include "../../../Game/Actor/Actor.h"
#include "../../Info/GameInfo.h"

struct PlayerStat
{
	float mHp;
	float mMaxHp;
	float mDef;
	float mSpeed;
};

class Player : public Actor
{
public:
	enum class PlayerType
	{
		Control,
		Defualt
	};

	Player(const std::weak_ptr<class Scene>& scene, PlayerInfo info, PlayerType type = PlayerType::Defualt);
	virtual ~Player() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void updateGravity(float deltatime);

	void collides(const std::weak_ptr<class BoxComponent>& bComp);
	virtual void setStat(PlayerInfo info);

private:
	PlayerType mType;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class BoxComponent> mBoxComponent;
	std::shared_ptr<class Actor> mHealthBar;
	float mGravitySpeed;

protected:
	PlayerStat mStat;
	std::shared_ptr<class MoveComponent> mMoveComponent;

private:
	std::shared_ptr<class RobotHead> mHead;
	std::shared_ptr<class RobotArm> mLeftArm;
	std::shared_ptr<class RobotArm> mRightArm;
	std::shared_ptr<class RobotLeg> mLeftLeg;
	std::shared_ptr<class RobotLeg> mRightLeg;

public:
	PlayerType getType() const { return mType; }
	void setPlayerTexture(const std::string& fileName);
	float getGravitySpeed() const { return mGravitySpeed; }
	void setGravitySpeed(float speed) { mGravitySpeed = speed; }
};