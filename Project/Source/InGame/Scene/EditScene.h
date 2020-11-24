#pragma once
#include "../Info/GameInfo.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/Math/Math.h"

class EditScene : public Scene
{
public:
	EditScene(const std::weak_ptr<class Game>& game, GameInfo info);
	virtual ~EditScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();
	bool loadGameMap();
	void loadBoard();

private:
	std::shared_ptr<class GameMap> mGameMap;
	std::unique_ptr<class MapEditor> mEditor;
	std::unique_ptr<class SceneHelper> mSceneHelper;
	GameInfo mInfo;
	int mStage;
};
