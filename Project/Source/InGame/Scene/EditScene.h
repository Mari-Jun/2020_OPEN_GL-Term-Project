#pragma once
#include "../Info/GameInfo.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/Math/Math.h"

class EditScene : public Scene
{
public:
	EditScene(const std::weak_ptr<class Game>& game, GameInfo info, int stage);
	virtual ~EditScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void draw();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();


	bool loadGameMap(const std::string& time = "None");
	void loadBoard(std::string&& name, Vector3&& position);

private:
	std::shared_ptr<class GameMap> mGameMap;
	std::unique_ptr<class MapEditor> mEditor;
	std::unique_ptr<class SceneHelper> mSceneHelper;
	GameInfo mInfo;
	std::shared_ptr<class EditHUD> mEditHUD;
	int mStage;

public:
	int getStage() const { return mStage; }
	void setStage(int stage) { mStage = stage; }
};
