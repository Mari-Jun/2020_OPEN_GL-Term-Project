#include "GameHUD.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"


GameHUD::GameHUD(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render)
	:UI(scene, render)
{

}

GameHUD::~GameHUD()
{

}

void GameHUD::initailize()
{
	UI::initailize();
	mCoin = mRenderer.lock()->getTexture("Asset/Image/HUD/coin.png");
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
	drawTexture(shader, mCoin, Vector2(wSize.x / 2 - 150.0f, wSize.y / 2 - 50.0f));
}