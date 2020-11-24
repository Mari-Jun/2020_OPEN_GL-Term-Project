#pragma once
#include "../Player.h"
#define MINION_ANGLE 20

class DefaultMinion : public Player
{
public:
	DefaultMinion(const std::weak_ptr<class Scene>& scene, PlayerInfo info, const std::weak_ptr<class MinionAi>& ai);
	virtual ~DefaultMinion() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void setStat(PlayerInfo info) override;
	void moveforDFS();
	void settingforDFS();
	void SmoothRotate();
	bool ChangeTarget();

private:
	std::weak_ptr<class MinionAi> AiWay;
	std::pair<int, int> target;
	int targetIndex = -1;
	Vector3 targetPos;

private:
	void moveforDFS();
	bool ChangeTarget();

	Vector3 repos;
	Vector3 Repos;
	Vector3 deltarepos;
	Vector3 oldrepos;
};