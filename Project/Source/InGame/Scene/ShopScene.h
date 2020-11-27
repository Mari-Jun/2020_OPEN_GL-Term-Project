#pragma once
#include "../Info/GameInfo.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/Math/Math.h"

class ShopScene : public Scene
{
public:
	ShopScene(const std::weak_ptr<class Game>& game, GameInfo info);
	virtual ~ShopScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

private:
	std::unique_ptr<class SceneHelper> mSceneHelper;
	GameInfo mInfo;

private:
	void loadUI();


public:
	const GameInfo& getGameInfo() const { return mInfo; }
};
