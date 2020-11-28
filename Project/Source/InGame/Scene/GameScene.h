#pragma once
#include "../Info/GameInfo.h"
#include "../../Game/Scene/Scene.h"

class GameScene : public Scene
{
public:
	GameScene(const std::weak_ptr<class Game>& game, GameInfo info);
	virtual ~GameScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();
	
private:
	std::shared_ptr<class FollowCameraActor> mFollowCamera;
	std::shared_ptr<class GameMap> mGameMap;
	std::unique_ptr<class SceneHelper> mSceneHelper;
	GameInfo mInfo;

private:
	void loadActorData();
	void loadGameMap();
	void loadUI();
	void pauseGame();

public:
	void stageClear();
	void goToTitle();

public:
	const GameInfo& getGameInfo() const { return mInfo; }
	const std::shared_ptr<class GameMap>& getGameMap() const { return mGameMap; }
};
