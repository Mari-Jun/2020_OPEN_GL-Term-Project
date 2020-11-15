#pragma once
#include "../../Game/Scene/Scene.h"

class GameScene : public Scene
{
public:
	GameScene(const std::weak_ptr<class Game>& game);
	virtual ~GameScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();
	void loadActorData();
	void loadGameMap(int stage);

private:
	std::shared_ptr<class FollowCameraActor> mFollowCamera;
	std::shared_ptr<class GameMap> mGameMap;
};
