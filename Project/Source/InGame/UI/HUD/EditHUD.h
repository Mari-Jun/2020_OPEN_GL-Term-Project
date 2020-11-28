#pragma once
#include "HUD.h"

using vTexSet = std::vector<std::shared_ptr<class Texture>>;

class EditHUD : public HUD
{
public:
	EditHUD(const std::weak_ptr<class EditScene>& scene, const std::weak_ptr<class Renderer>& render);
	~EditHUD();

	virtual void initailize();
	virtual void resetInfo();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

	void setGameMap(const std::weak_ptr<class GameMap>& gameMap) { mGameMap = gameMap; }

private:
	std::weak_ptr<class EditScene> mEditScene;
	std::weak_ptr<class GameMap> mGameMap;
	std::shared_ptr<class Texture> mCountBoard;
	std::vector<std::shared_ptr<class Texture>> mMinionCount;
	std::shared_ptr<class Texture> mStageBoard;
	std::vector<std::shared_ptr<class Texture>> mStageCount;
};