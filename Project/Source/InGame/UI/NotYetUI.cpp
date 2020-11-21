#include "NotYetUI.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Scene/Scene.h"

NotYetUI::NotYetUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render)
	: UI(scene, render)
{

}

NotYetUI::~NotYetUI()
{

}

void NotYetUI::initailize()
{
	UI::initailize();

	auto game = mScene.lock()->getGame().lock();
	auto texture = game->getRenderer()->getTexture("Asset/Image/OKButton.png");
	addButton([this]() {closeUI(); }, Vector2(0.0f, -100.0f), texture);

	mBackground = game->getRenderer()->getTexture("Asset/Image/NotYet.png");
	mBackgroundPos = Vector2(0.0f, 0.0f);
}

void NotYetUI::processInput()
{
	UI::processInput();
}

