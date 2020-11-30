#include "StageHUD.h"
#include "../../Scene/TitleScene.h"
#include "../../Map/GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"
#include "../../../Game/Sound/Sound.h"

StageHUD::StageHUD(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, const GameInfo& info)
	: HUD(scene, render)
	, mInfo(info)
	, mStage(mInfo.mStage)	
{

}

StageHUD::~StageHUD()
{
	if (mScene.lock()->getSceneState() != (Scene::SceneState::Dead))
	{
		mScene.lock()->setSceneState(Scene::SceneState::Active);
	}
}

void StageHUD::initailize()
{
	HUD::initailize();

	auto game = mScene.lock()->getGame().lock();
	game->getSound()->play(static_cast<int>(Sound::Type::ui), static_cast<int>(Sound::uiName::notice), 2);

	addButton([this]() {back(); }, Vector2(-140.0f, 80.0f), "Asset/Image/Button/BackButton");
	addButton([this]() {next(); }, Vector2(140.0f, 80.0f), "Asset/Image/Button/NextButton");
	addButton([this]() {play(); }, Vector2(0.0f, -50.0f), "Asset/Image/Button/PlayButton");
	addButton([this]() {closeUI(); }, Vector2(0.0f, -160.0f), "Asset/Image/Button/HomeButton");
	mBackgroundPos = Vector2(0.0f, 0.0f);
	mScene.lock()->setSceneState(Scene::SceneState::Paused);

	resetInfo();
}

void StageHUD::resetInfo()
{
	mStageCount.clear();
	setNumberTexture(mStageCount, mStage, "Asset/Image/HUD/RNum");
}

void StageHUD::update(float deltatime)
{

}

void StageHUD::processInput()
{
	UI::processInput();
}

void StageHUD::draw(std::unique_ptr<class Shader>& shader)
{
	UI::draw(shader);

	auto wSize = mRenderer.lock()->getWindow()->getSize();
	drawNumberTexture(shader, mStageCount, Vector2(50.0f, 80.0f), 35.0f);
}

void StageHUD::back()
{
	if (mStage > 1)
	{
		mStage--;
		resetInfo();
	}
}

void StageHUD::next()
{
	if (mStage < mInfo.mStage)
	{
		mStage++;
		resetInfo();
	}
}

void StageHUD::play()
{
	auto scene = std::dynamic_pointer_cast<TitleScene>(mScene.lock());
	closeUIWarp();
	scene->playGame(mStage);
}