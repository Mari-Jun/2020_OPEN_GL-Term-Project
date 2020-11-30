#include "UI.h"
#include "Button.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Input/Mouse.h"
#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Shader/Shader.h"
#include "../Sound/Sound.h"
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
	
	for (const auto& button : mButtons)
	{
		if (button->containMouse(mousePos))
		{
			if(!button->getOnButton())
				mScene.lock()->getGame().lock()->getSound()->play(static_cast<int>(Sound::Type::ui), static_cast<int>(Sound::uiName::select), 1);
			button->setOnButton(true);
		}
		else
		{
			button->setOnButton(false);
		}
	}

	auto click = mScene.lock()->getGame().lock()->getMouse()->getState(GLUT_LEFT_BUTTON) &&
		mScene.lock()->getGame().lock()->getMouse()->getFirst(GLUT_LEFT_BUTTON);
	if (click)
	{
		for (const auto& button : mButtons)
		{
			if (button->getOnButton())
			{
				mScene.lock()->getGame().lock()->getSound()->play(static_cast<int>(Sound::Type::ui), static_cast<int>(Sound::uiName::click), 1);
				button->click();
			}
		}
	}
}

void UI::draw(std::unique_ptr<Shader>& shader)
{
	drawTexture(shader, mBackground, mBackgroundPos);	

	for (const auto& button : mButtons)
	{
		button->draw(shader);
	}
}

void UI::drawTexture(std::unique_ptr<Shader>& shader, const std::shared_ptr<class Texture>& texture, const Vector2& pos)
{
	if (texture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(texture->getWidth()), static_cast<float>(texture->getHeight()), 1.0f);
		Matrix4 world = scaleMat * Matrix4::CreateTranslation(Vector3(pos.x, pos.y, 0.0f));
		shader->setMatrixUniform("uWorldTransform", world);

		texture->setActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void UI::addButton(std::function<void()> click, const Vector2& pos, const std::string& fileName)
{
	auto game = mScene.lock()->getGame().lock();
	auto button = std::make_shared<Button>(click, pos);
	button->setTexture(game->getRenderer()->getTexture(fileName + ".png"), game->getRenderer()->getTexture(fileName + "On.png"));
	mButtons.emplace_back(button);
}

void UI::closeUI()
{
	mState = UIState::Dead;
}

void UI::closeUIWarp()
{
	closeUI();
	auto game = mScene.lock()->getGame().lock();
	game->getMouse()->setCursor(GLUT_CURSOR_NONE);
	game->getMouse()->setWarp(true);
}