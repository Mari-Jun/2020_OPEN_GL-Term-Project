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
	virtual void draw();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

private:
	std::unique_ptr<class SceneHelper> mSceneHelper;
	std::shared_ptr<class ShopHUD> mShopHUD;
	GameInfo mInfo;
	std::shared_ptr<class Player> mControl;
	std::shared_ptr<class Player> mMinion;

private:
	void loadUI();
	void loadPlayer();
	void upgradeStatLevel(int& statLevel, const std::string& type);
	void changeSkin(std::shared_ptr<class Player>& player, PlayerInfo& info, bool next);

public:
	const GameInfo& getGameInfo() const { return mInfo; }
};
