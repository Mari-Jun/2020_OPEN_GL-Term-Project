#include "ShopHUD.h"
#include "../../Scene/ShopScene.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"


ShopHUD::ShopHUD(const std::weak_ptr<class ShopScene>& scene, const std::weak_ptr<class Renderer>& render)
	: UI(scene, render)
	, mShopScene(scene)
{

}

ShopHUD::~ShopHUD()
{

}

void ShopHUD::initailize()
{
	UI::initailize();
	mCoin = mRenderer.lock()->getTexture("Asset/Image/HUD/coin.png");

	loadCoinNumber();
	loadPlayerStat();

	mReinForceBoard = mRenderer.lock()->getTexture("Asset/Image/ShopScene/Reinforce.png");
}

void ShopHUD::loadCoinNumber()
{
	setNumberTexture(mCoinNumber, mShopScene.lock()->getGameInfo().mCoin, "Asset/Image/HUD/Num");
}

void ShopHUD::loadPlayerStat()
{
	auto hp = mShopScene.lock()->getGameInfo().mControlInfo.getHpStat(PlayerInfo::Type::Control);
	setNumberTexture(mPlayerStat.mHpNumber, hp, "Asset/Image/ShopScene/Num");
	
	auto def = mShopScene.lock()->getGameInfo().mControlInfo.getDefStat(PlayerInfo::Type::Control);
	auto speed = mShopScene.lock()->getGameInfo().mControlInfo.getSpeedStat(PlayerInfo::Type::Control);
}
void ShopHUD::loadMinionStat()
{

}

void ShopHUD::update(float deltatime)
{

}

void ShopHUD::processInput()
{

}

void ShopHUD::draw(std::unique_ptr<class Shader>& shader)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();
	drawTexture(shader, mCoin, Vector2(wSize.x / 2 - 50.0f * (mCoinNumber.size() + 2), wSize.y / 2 - 50.0f));

	drawNumberTexture(shader, mCoinNumber, Vector2(wSize.x / 2, wSize.y / 2 - 50.0f), 50.0f);

	drawTexture(shader, mReinForceBoard, Vector2(-wSize.x / 2 + mReinForceBoard->getWidth() / 2 + 50.0f, 0.0f));

	drawNumberTexture(shader, mPlayerStat.mHpNumber, Vector2(-230.0f, wSize.y / 2 - 140.0f), 35.0f);
}


void ShopHUD::setNumberTexture(vTexSet& texture, int info, const std::string& fileName)
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

void ShopHUD::drawNumberTexture(std::unique_ptr<class Shader>& shader, const vTexSet& texture, const Vector2& pos, float gap)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();

	for (auto iter = texture.crbegin(); iter != texture.crend(); ++iter)
	{
		auto xPos = pos.x - (gap * (texture.crend() - iter));
		drawTexture(shader, *iter, Vector2(xPos, pos.y));
	}
}