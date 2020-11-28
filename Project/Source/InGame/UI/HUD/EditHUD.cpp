#include "EditHUD.h"
#include "../../Scene/EditScene.h"
#include "../../Map/GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"


EditHUD::EditHUD(const std::weak_ptr<class EditScene>& scene, const std::weak_ptr<class Renderer>& render, const std::weak_ptr<class GameMap>& map)
	: UI(scene, render)
	, mEditScene(scene)
	, mGameMap(map)
{

}

EditHUD::~EditHUD()
{

}

void EditHUD::initailize()
{
	UI::initailize();

	auto number = mGameMap.lock()->getMinionCount();
	mCountBoard = mRenderer.lock()->getTexture("Asset/Image/EditScene/MinionCount.png");
	setNumberTexture(mMinionCount, number, "Asset/Image/ShopScene/Num");
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
}

void EditHUD::setNumberTexture(vTexSet& texture, int info, const std::string& fileName)
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

void EditHUD::drawNumberTexture(std::unique_ptr<class Shader>& shader, const vTexSet& texture, const Vector2& pos, float gap)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();

	for (auto iter = texture.crbegin(); iter != texture.crend(); ++iter)
	{
		auto xPos = pos.x - (gap * (texture.crend() - iter));
		drawTexture(shader, *iter, Vector2(xPos, pos.y));
	}
}