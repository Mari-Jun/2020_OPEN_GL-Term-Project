#pragma once
#include "../Player.h"

class DefaultMinion : public Player
{
public:
	DefaultMinion(const std::weak_ptr<class Scene>& scene, PlayerInfo info, const std::weak_ptr<class MinionAi>& ai);
	virtual ~DefaultMinion() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	virtual void setStat(PlayerInfo info) override;

private:
	std::weak_ptr<class MinionAi> AiWay;
	std::pair<int, int> target;
	int targetIndex = 0;
	Vector3 targetPos;

private:
	void moveforDFS();
	bool ChangeTarget();
};