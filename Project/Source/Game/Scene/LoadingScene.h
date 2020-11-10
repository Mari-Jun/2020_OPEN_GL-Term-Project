#pragma once
#include "Scene.h"

class LoadingScene : public Scene
{
public:
	LoadingScene(const std::weak_ptr<class Game>& game);
	virtual ~LoadingScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

private:
	std::shared_ptr<class FollowCameraActor> mFollowCamera;
};
