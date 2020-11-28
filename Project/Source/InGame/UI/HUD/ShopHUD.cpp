#include "ShopHUD.h"
#include "../../Scene/ShopScene.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"


ShopHUD::ShopHUD(const std::weak_ptr<class ShopScene>& scene, const std::weak_ptr<class Renderer>& render)
	: HUD(scene, render)
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
	mReinForceBoard = mRenderer.lock()->getTexture("Asset/Image/ShopScene/Reinforce.png");
	mSkin1 = mRenderer.lock()->getTexture("Asset/Image/ShopScene/skinBox.png");
	mSkin2 = mRenderer.lock()->getTexture("Asset/Image/ShopScene/skinBox.png");
	resetInfo();
}

void ShopHUD::resetInfo()
{
	loadCoinNumber();
	loadStat(mShopScene.lock()->getGameInfo().mControlInfo, mPlayerStat);
	loadStat(mShopScene.lock()->getGameInfo().mMinionInfo, mMinionStat);
}

void ShopHUD::loadCoinNumber()
{
	mCoinNumber.clear();
	setNumberTexture(mCoinNumber, mShopScene.lock()->getGameInfo().mCoin, "Asset/Image/HUD/Num");
}

void ShopHUD::loadStat(const PlayerInfo& info, StatNumber& stat)
{
	stat.mHpNumber.clear();
	stat.mDefNumber.clear();
	stat.mSpeedNumber.clear();

	const std::string fileName = "Asset/Image/ShopScene/Num";
	auto hp = info.getHpStat();
	setNumberTexture(stat.mHpNumber, hp, fileName);

	auto def = info.getDefStat();
	setNumberTexture(stat.mDefNumber, def, fileName);

	auto speed = info.getSpeedStat();
	setNumberTexture(stat.mSpeedNumber, speed, fileName);
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

	drawNumberTexture(shader, mPlayerStat.mHpNumber, Vector2(-210.0f, wSize.y / 2 - 140.0f), 35.0f);
	drawNumberTexture(shader, mPlayerStat.mDefNumber, Vector2(-210.0f, wSize.y / 2 - 240.0f), 35.0f);
	drawNumberTexture(shader, mPlayerStat.mSpeedNumber, Vector2(-210.0f, wSize.y / 2 - 340.0f), 35.0f);
	drawNumberTexture(shader, mMinionStat.mHpNumber, Vector2(-210.0f, wSize.y / 2 - 440.0f), 35.0f);
	drawNumberTexture(shader, mMinionStat.mDefNumber, Vector2(-210.0f, wSize.y / 2 - 540.0f), 35.0f);
	drawNumberTexture(shader, mMinionStat.mSpeedNumber, Vector2(-210.0f, wSize.y / 2 - 640.0f), 35.0f);

	drawTexture(shader, mSkin1, Vector2(wSize.x / 2 - mSkin1->getWidth() / 2 - 20.0f, 180.0f));
	drawTexture(shader, mSkin2, Vector2(wSize.x / 2 - mSkin2->getWidth() / 2 - 20.0f, -120.0f));
}