#include "GameHUD.h"
#include "../../Scene/GameScene.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"


GameHUD::GameHUD(const std::weak_ptr<class GameScene>& scene, const std::weak_ptr<class Renderer>& render)
	: HUD(scene, render)
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
	resetInfo();
}

void GameHUD::resetInfo()
{
	mCoinNumber.clear();
	setNumberTexture(mCoinNumber, mGameScene.lock()->getGameInfo().mCoin, "Asset/Image/HUD/Num");
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
	drawNumberTexture(shader, mCoinNumber, Vector2(wSize.x / 2, wSize.y / 2 - 50.0f), 50.0f);
}