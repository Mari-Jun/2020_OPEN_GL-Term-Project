#include "PauseUI.h"
#include "SceneHelper.h"
#include "../../Game/Game.h"
#include "../../Game/Scene/Scene.h"
#include "../Scene/GameScene.h"

PauseUI::PauseUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render)
	: UI(scene, render)
{

}

PauseUI::~PauseUI()
{
	if (mScene.lock()->getState() != (Scene::State::Dead))
	{
		mScene.lock()->setState(Scene::State::Active);
	}
}

void PauseUI::initailize()
{
	UI::initailize();

	auto game = mScene.lock()->getGame().lock();
	addButton([this]() {closeUIWarp(); }, Vector2(0.0f, 0.0f), "Asset/Image/Button/PlayButton");
	addButton([this]() {goToTitle(); }, Vector2(0.0f, -110.0f), "Asset/Image/Button/HomeButton");
	mBackgroundPos = Vector2(0.0f, 0.0f);
	mScene.lock()->setState(Scene::State::Paused);
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