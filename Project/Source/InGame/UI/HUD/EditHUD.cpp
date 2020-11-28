#include "EditHUD.h"
#include "../../Scene/EditScene.h"
#include "../../Map/GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"


EditHUD::EditHUD(const std::weak_ptr<class EditScene>& scene, const std::weak_ptr<class Renderer>& render)
	: HUD(scene, render)
	, mEditScene(scene)
{

}

EditHUD::~EditHUD()
{

}

void EditHUD::initailize()
{
	UI::initailize();
	mCountBoard = mRenderer.lock()->getTexture("Asset/Image/EditScene/MinionCount.png");
	mStageBoard = mRenderer.lock()->getTexture("Asset/Image/EditScene/Stage.png");
}

void EditHUD::resetInfo()
{
	mMinionCount.clear();
	setNumberTexture(mMinionCount, mGameMap.lock()->getMinionCount(), "Asset/Image/HUD/RNum");
	mStageCount.clear();
	setNumberTexture(mStageCount, mEditScene.lock()->getStage(), "Asset/Image/HUD/RNum");
}

void EditHUD::update(float deltatime)
{

}

void EditHUD::processInput()
{

}

void EditHUD::draw(std::unique_ptr<class Shader>& shader)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();
	drawTexture(shader, mCountBoard, Vector2(0.0f, -wSize.y / 2 + 50.0f));
	drawNumberTexture(shader, mMinionCount, Vector2(150.0f, -wSize.y / 2 + 50.0f), 35.0f);
	drawTexture(shader, mStageBoard, Vector2(0.0f, wSize.y / 2 - 35.0f));
	drawNumberTexture(shader, mStageCount, Vector2(150.0f, wSize.y / 2 - 35.0f), 35.0f);
}