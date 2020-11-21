#pragma once
#include "../../Game/Scene/Scene.h"
#include "../../Game/Math/Math.h"

class TitleScene : public Scene
{
public:
	TitleScene(const std::weak_ptr<class Game>& game, int stage = 1);
	virtual ~TitleScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

private:
	std::unique_ptr<class SceneHelper> mSceneHelper;
	int mStage; //�ӽ�
};
