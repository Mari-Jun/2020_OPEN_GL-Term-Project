#pragma once
#include "HUD.h"

class GameHUD : public HUD
{
public:
	GameHUD(const std::weak_ptr<class GameScene>& scene, const std::weak_ptr<class Renderer>& render);
	~GameHUD();

	virtual void initailize();
	virtual void resetInfo();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

	void setIsPhoto(bool photo) { mIsPhoto = photo; }

private:
	bool mIsPhoto;
	std::weak_ptr<class GameScene> mGameScene;
	std::shared_ptr<class Texture> mCoin;
	std::vector<std::shared_ptr<class Texture>> mCoinNumber;
	std::vector<std::shared_ptr<class Texture>> mLiveMinion;
	std::shared_ptr<class Texture> mCross;
	std::vector<std::shared_ptr<class Texture>> mClearMinion;
};