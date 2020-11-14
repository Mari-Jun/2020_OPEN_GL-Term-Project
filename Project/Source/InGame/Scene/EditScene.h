#pragma once
#include "../../Game/Scene/Scene.h"

class EditScene : public Scene
{
public:
	EditScene(const std::weak_ptr<class Game>& game);
	virtual ~EditScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();
	bool loadGameMap();

private:
	std::shared_ptr<class GameMap> mGameMap;
	std::unique_ptr<class MapEditor> mEditor;
	int mStage;
};
