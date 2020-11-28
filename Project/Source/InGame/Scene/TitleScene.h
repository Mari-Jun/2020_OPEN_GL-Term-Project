#pragma once
#include "../Info/GameInfo.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/Math/Math.h"

class TitleScene : public Scene
{
public:
	TitleScene(const std::weak_ptr<class Game>& game, GameInfo info);
	virtual ~TitleScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

	void playGame(int stage);

private:
	std::unique_ptr<class SceneHelper> mSceneHelper;
	GameInfo mInfo;

private:
	void selectStage();
};
