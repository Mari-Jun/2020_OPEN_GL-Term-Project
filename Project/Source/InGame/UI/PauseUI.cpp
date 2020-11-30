#include "PauseUI.h"
#include "SceneHelper.h"
#include "../../Game/Game.h"
#include "../../Game/Scene/Scene.h"
#include "../Scene/GameScene.h"
#include "../../Game/Sound/Sound.h"

PauseUI::PauseUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, UIType type)
	: UI(scene, render)
	, mType(type)
{

}

PauseUI::~PauseUI()
{
	if (mScene.lock()->getSceneState() != (Scene::SceneState::Dead))
	{
		mScene.lock()->setSceneState(Scene::SceneState::Active);
	}
}

void PauseUI::initailize()
{
	UI::initailize();

	auto game = mScene.lock()->getGame().lock();
	game->getSound()->play(static_cast<int>(Sound::Type::ui), static_cast<int>(Sound::uiName::notice), 2);
	if (mType == UIType::Pause)
	{
		addButton([this]() {closeUIWarp(); }, Vector2(0.0f, 0.0f), "Asset/Image/Button/PlayButton");
	}
	addButton([this]() {goToTitle(); }, Vector2(0.0f, -110.0f), "Asset/Image/Button/HomeButton");
	mBackgroundPos = Vector2(0.0f, 0.0f);
	mScene.lock()->setSceneState(Scene::SceneState::Paused);
}

void PauseUI::processInput()
{
	UI::processInput();
}

void PauseUI::goToTitle()
{
	auto scene = std::dynamic_pointer_cast<GameScene>(mScene.lock());
	closeUIWarp();
	scene->goToTitle();
}