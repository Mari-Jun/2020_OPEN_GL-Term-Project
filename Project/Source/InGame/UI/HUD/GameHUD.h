#pragma once
#include "../../../Game/UI/UI.h"

class GameHUD : public UI
{
public:
	GameHUD(const std::weak_ptr<class GameScene>& scene, const std::weak_ptr<class Renderer>& render);
	~GameHUD();

	virtual void initailize();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

private:
	std::weak_ptr<class GameScene> mGameScene;
	std::shared_ptr<class Texture> mCoin;
	std::vector<std::shared_ptr<class Texture>> mCoinNumber;
};