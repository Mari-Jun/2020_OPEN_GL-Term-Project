#pragma once
#include "../Info/GameInfo.h"
#include "../../Game/Scene/Scene.h"

class GameScene : public Scene
{
public:
	GameScene(const std::weak_ptr<class Game>& game, GameInfo info, int stage);
	virtual ~GameScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();
	
	virtual void draw();

private:
	std::shared_ptr<class ControlPlayer> mControl;
	std::shared_ptr<class FollowCameraActor> mFollowCamera;
	std::shared_ptr<class CameraActor> mPhotoCamera;
	std::shared_ptr<class ParticleCreator> mParticle;
	std::shared_ptr<class MinionManager> mMinionManager;
	std::shared_ptr<class GameMap> mGameMap;
	std::unique_ptr<class SceneHelper> mSceneHelper;
	std::shared_ptr<class GameHUD> mGameHUD;
	std::shared_ptr<class CubeMaps> mCubeMaps;
	GameInfo mInfo;
	int mStage;

private:
	void loadActorData();
	void loadGameMap();
	void loadUI();
	void pauseGame(const std::string& type);
	void changeGameToPhoto();
	void changePhotoToGame();

public:
	void stageClear();
	void stageFail();
	void goToTitle();

public:
	const GameInfo& getGameInfo() const { return mInfo; }
	const std::shared_ptr<class GameMap>& getGameMap() const { return mGameMap; }
	const std::shared_ptr<class MinionManager>& getManager() const { return mMinionManager; }
	const std::shared_ptr<class GameHUD>& getGameHUD() const { return mGameHUD; }
};
