#include "DialogUI.h"
#include "../../Game/Game.h"
#include "../../Game/Scene/Scene.h"

DialogUI::DialogUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render)
	: UI(scene, render)
{

}

DialogUI::~DialogUI()
{
	mScene.lock()->setState(Scene::State::Active);
}

void DialogUI::initailize()
{
	UI::initailize();

	auto game = mScene.lock()->getGame().lock();
	addButton([this]() {closeUI(); }, Vector2(0.0f, -100.0f), "Asset/Image/Button/OKButton");
	mBackgroundPos = Vector2(0.0f, 0.0f);
	mScene.lock()->setState(Scene::State::Paused);
}

void DialogUI::processInput()
{
	UI::processInput();
}

