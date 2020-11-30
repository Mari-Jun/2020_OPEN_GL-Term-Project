#include "LoadingHUD.h"
#include "../../Scene/LoadingScene.h"
#include "../../Map/GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"


LoadingHUD::LoadingHUD(const std::weak_ptr<class LoadingScene>& scene, const std::weak_ptr<class Renderer>& render)
	: HUD(scene, render)
	, mLoadingScene(scene)
{

}

LoadingHUD::~LoadingHUD()
{

}

void LoadingHUD::initailize()
{
}

void LoadingHUD::resetInfo()
{
}

void LoadingHUD::update(float deltatime)
{

}

void LoadingHUD::processInput()
{

}

void LoadingHUD::draw(std::unique_ptr<class Shader>& shader)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();
	drawTexture(shader, mCountBoard, Vector2(0.0f, -wSize.y / 2 + 50.0f));
	drawNumberTexture(shader, mMinionCount, Vector2(150.0f, -wSize.y / 2 + 50.0f), 35.0f);
	drawTexture(shader, mStageBoard, Vector2(0.0f, wSize.y / 2 - 35.0f));
	drawNumberTexture(shader, mStageCount, Vector2(150.0f, wSize.y / 2 - 35.0f), 35.0f);
}