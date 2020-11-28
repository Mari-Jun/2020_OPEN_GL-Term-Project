#pragma once
#include "../MovePlayer.h"
#define MINION_ANGLE 20

class DefaultMinion : public MovePlayer
{
public:
	DefaultMinion(const std::weak_ptr<class Scene>& scene, PlayerInfo info, const std::weak_ptr<class MinionManager>& manager);
	virtual ~DefaultMinion() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	void endPoint();

private:
	std::weak_ptr<class MinionManager> mManager;
	std::pair<int, int> target;
	int targetIndex = -1;
	Vector3 targetPos;

private:
	virtual void setStat(PlayerInfo info) override;
	virtual void checkHp() override;

private:
	void moveforDFS();
	void settingforDFS();
	void SmoothRotate();
	bool ChangeTarget();

	Vector3 repos;
	Vector3 Repos;
	Vector3 deltarepos;
	Vector3 oldrepos;
};