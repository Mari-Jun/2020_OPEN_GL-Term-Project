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
	auto number = mShopScene.lock()->getGameInfo().mCoin;
	std::string fileName = "Asset/Image/HUD/Num";

	if (number == 0)
	{
		mCoinNumber.push_back(mRenderer.lock()->getTexture(fileName + "0.png"));
	}
	else
	{
		while (number != 0)
		{
			mCoinNumber.push_back(mRenderer.lock()->getTexture(fileName + std::to_string(number % 10) + ".png"));
			number /= 10;
		}
	}
}

void ShopHUD::loadPlayerStat()
{
	auto num = mShopScene.lock()->getGameInfo().mControlInfo.getHpStat(PlayerInfo::Type::Control);
	auto def = mShopScene.lock()->getGameInfo().mControlInfo.getDefStat(PlayerInfo::Type::Control);
	auto speed = mShopScene.lock()->getGameInfo().mControlInfo.getSpeedStat(PlayerInfo::Type::Control);

	std::string fileName = "Asset/Image/ShopScene/Num";

	if (num == 0)
	{
		mPlayerStat.mHpNumber.push_back(mRenderer.lock()->getTexture(fileName + "0.png"));
	}
	else
	{
		while (num != 0)
		{
			mPlayerStat.mHpNumber.push_back(mRenderer.lock()->getTexture(fileName + std::to_string(num % 10) + ".png"));
			num /= 10;
		}
	}
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

	drawNumberTexture(shader, mCoinNumber, Vector2(wSize.x / 2, wSize.y / 2 - 50.0f));

	drawTexture(shader, mReinForceBoard, Vector2(-wSize.x / 2 + mReinForceBoard->getWidth() / 2 + 50.0f, 0.0f));

	drawNumberTexture(shader, mPlayerStat.mHpNumber, Vector2(-150.0f, wSize.y / 2 - 100.0f));
}


void ShopHUD::setNumberTexture(vTexSet& texture, const std::string& fileName)
{

}

void ShopHUD::drawNumberTexture(std::unique_ptr<class Shader>& shader, const vTexSet& texture, const Vector2& pos)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();

	for (auto iter = texture.crbegin(); iter != texture.crend(); ++iter)
	{
		auto xPos = pos.x - (50.0f * (texture.crend() - iter));
		drawTexture(shader, *iter, Vector2(xPos, pos.y));
	}
}