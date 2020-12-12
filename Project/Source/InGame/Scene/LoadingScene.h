#pragma once
#include "../../Game/Scene/Scene.h"

static int loadercount;

class LoadingScene : public Scene
{
public:
	LoadingScene(const std::weak_ptr<class Game>& game);
	virtual ~LoadingScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void draw();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

private:
	int count;
	std::shared_ptr<class LoadingHUD> mLoadingHUD;
	bool loadtexture();
	std::vector<std::string> mLoader;
	std::vector<std::string> mMeshLoader;

};
