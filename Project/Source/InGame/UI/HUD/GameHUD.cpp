#include "GameHUD.h"
#include "../../Scene/GameScene.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"


GameHUD::GameHUD(const std::weak_ptr<class GameScene>& scene, const std::weak_ptr<class Renderer>& render)
	: UI(scene, render)
	, mGameScene(scene)
{

}

GameHUD::~GameHUD()
{

}

void GameHUD::initailize()
{
	UI::initailize();
	mCoin = mRenderer.lock()->getTexture("Asset/Image/HUD/coin.png");

	auto number = mGameScene.lock()->getGameInfo().mCoin;
	std::string fileName = "Asset/Image/HUD/Num";

	if (number == 0)
	{
		mCoinNumber.push_back(mRenderer.lock()->getTexture(fileName + "0.png"));
	}
	else
	{
		while (number != 0)
		{
			mCoinNumber.push_back(mRenderer.lock()->getTexture(fileName + std::to_string(number % 10) + ".png"));
			number /= 10;
		}
	}
}

void GameHUD::update(float deltatime)
{

}

void GameHUD::processInput()
{

}

void GameHUD::draw(std::unique_ptr<class Shader>& shader)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();
	drawTexture(shader, mCoin, Vector2(wSize.x / 2 - 50.0f * (mCoinNumber.size() + 2), wSize.y / 2 - 50.0f));

	for (auto iter = mCoinNumber.crbegin(); iter != mCoinNumber.crend(); ++iter)
	{
		auto xPos = wSize.x / 2 - (50.0f * (mCoinNumber.crend() - iter));
		drawTexture(shader, *iter, Vector2(xPos, wSize.y / 2 - 50.0f));
	}
}