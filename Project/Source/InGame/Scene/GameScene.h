#pragma once
#include "../../Game/Scene/Scene.h"

class GameScene : public Scene
{
public:
	GameScene(const std::weak_ptr<class Game>& game, int stage = 1);
	virtual ~GameScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();
	
private:
	std::shared_ptr<class FollowCameraActor> mFollowCamera;
	std::shared_ptr<class GameMap> mGameMap;
	std::shared_ptr<class MinionAi> mMinionAi;
	int mStage;

private:
	void loadActorData();
	void loadGameMap();
	void loadUI();
};
