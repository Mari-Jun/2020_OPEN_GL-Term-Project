#include "GameHUD.h"
#include "../../Scene/GameScene.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../Actor/Player/Type/MinionAi/MinionManager.h"


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
	HUD::initailize();
	mCoin = mRenderer.lock()->getTexture("Asset/Image/HUD/coin.png");
	mCross = mRenderer.lock()->getTexture("Asset/Image/HUD/Cross.png");

	resetInfo();
}

void GameHUD::resetInfo()
{
	mCoinNumber.clear();
	setNumberTexture(mCoinNumber, mGameScene.lock()->getGameInfo().mCoin, "Asset/Image/HUD/YNum");

	const auto& manager = mGameScene.lock()->getManager();
	mLiveMinion.clear();
	setNumberTexture(mLiveMinion, manager->getLiveMinion(), "Asset/Image/HUD/RNum");
	mClearMinion.clear();
	setNumberTexture(mClearMinion, manager->getClearMinion(), "Asset/Image/HUD/RNum");
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

	drawTexture(shader, mCross, Vector2(0.0f, wSize.y / 2 - 50.0f));
	drawNumberTexture(shader, mLiveMinion, Vector2(0.0f, wSize.y / 2 - 50.0f), 35.0f);
	drawNumberTexture(shader, mClearMinion, Vector2(35.0f * (mClearMinion.size() + 1), wSize.y / 2 - 50.0f), 35.0f);
}