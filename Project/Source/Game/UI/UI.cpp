#include "UI.h"
#include "Button.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Input/Mouse.h"
#include "../Graphics/Texture/Texture.h"

UI::UI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render)
	: mState(UIState::Active)
	, mScene(scene)
	, mRenderer(render)
{

}

UI::~UI()
{
	for (auto& button : mButtons)
	{
		button.reset();
	}
	mButtons.clear();

	mRenderer.lock()->removeUI(weak_from_this());
}

void UI::initailize()
{
	mScene.lock()->addUI(shared_from_this());
	mRenderer.lock()->addUI(weak_from_this());
}

void UI::update(float deltatime)
{

}

void UI::processInput()
{
	const auto& mousePos = mScene.lock()->getGame().lock()->getMouse()->getPosition();
	auto click = mScene.lock()->getGame().lock()->getMouse()->getState(GLUT_LEFT_BUTTON) && 
		mScene.lock()->getGame().lock()->getMouse()->getFirst(GLUT_LEFT_BUTTON);
	for (const auto& button : mButtons)
	{
		if (button->containMouse(mousePos) && click)
		{
			button->click();
		}
	}
}

void UI::draw(std::unique_ptr<Shader>& shader)
{
	for (const auto& button : mButtons)
	{
		button->draw(shader);
	}
}

void UI::addButton(std::function<void()> click, const Vector2& pos, const std::shared_ptr<Texture>& texture)
{
	auto button = std::make_shared<Button>(click, pos, texture);
	mButtons.emplace_back(button);
}

void UI::closeUI()
{
	mState = UIState::Dead;
}