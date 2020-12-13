#pragma once
#include "../Info/GameInfo.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/Math/Math.h"

class SettingScene : public Scene
{
public:
	SettingScene(const std::weak_ptr<class Game>& game, GameInfo info);
	virtual ~SettingScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void draw();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

	void playGame(int stage);

private:
	void loadUI();
	std::unique_ptr<class SceneHelper> mSceneHelper;
	GameInfo mInfo;
	std::shared_ptr<class SettingHUD> mSettingHUD;

private:
	void selectStage();
};
