#include "HUD.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"


HUD::HUD(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render)
	: UI(scene, render)
{

}

HUD::~HUD()
{

}

void HUD::initailize()
{
	UI::initailize();
}

void HUD::update(float deltatime)
{

}

void HUD::processInput()
{

}

void HUD::draw(std::unique_ptr<class Shader>& shader)
{

}

void HUD::setNumberTexture(vTexSet& texture, int info, const std::string& fileName)
{
	auto number = info;

	if (number == 0)
	{
		texture.push_back(mRenderer.lock()->getTexture(fileName + "0.png"));
	}
	else
	{
		while (number != 0)
		{
			texture.push_back(mRenderer.lock()->getTexture(fileName + std::to_string(number % 10) + ".png"));
			number /= 10;
		}
	}
}

void HUD::drawNumberTexture(std::unique_ptr<class Shader>& shader, const vTexSet& texture, const Vector2& pos, float gap)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();

	for (auto iter = texture.crbegin(); iter != texture.crend(); ++iter)
	{
		auto xPos = pos.x - (gap * (texture.crend() - iter));
		drawTexture(shader, *iter, Vector2(xPos, pos.y));
	}
}