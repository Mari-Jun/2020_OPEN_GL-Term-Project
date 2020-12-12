#include <string>
#include "ShopScene.h"
#include "../../Game/Graphics/Window.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Input/Mouse.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"
#include "../../Game/Sound/Sound.h"
#include "../../Game/UI/UI.h"
#include "../UI/SceneHelper.h"
#include "../UI/HUD/ShopHUD.h"
#include "../Actor/Player/Player.h"
#include "../../Game/Graphics/Light/Light.h"

ShopScene::ShopScene(const std::weak_ptr<class Game>& game, GameInfo info)
	: Scene(game)
	, mInfo(info)
{

}

ShopScene::~ShopScene()
{

}

void ShopScene::initailize()
{
	Scene::initailize();

	auto game = getGame().lock();

	//SetMouse
	game->getMouse()->setCursor(GLUT_CURSOR_INHERIT);
	game->getMouse()->setWarp(false);

	//Set View
	auto windowSize = getGame().lock()->getRenderer()->getWindow()->getSize();
	auto view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitZ, Vector3::UnitY);
	auto projection = Matrix4::CreateOrtho(windowSize.x / 10.0f, windowSize.y / 10.0f, 0.0f, 5.0f);
	getGame().lock()->getRenderer()->setViewMatrix(view);
	getGame().lock()->getRenderer()->setProjectionMatrix(projection);
	getGame().lock()->getRenderer()->getLight()->setAmbientLight(Vector3(0.4f, 0.4f, 0.4f));

	loadData();

	//Set Sound
	game->getSound()->play(static_cast<int>(Sound::Type::bgm), static_cast<int>(Sound::bgmName::Edit), 0);
}

void ShopScene::sceneInput()
{
	Scene::sceneInput();

	auto game = getGame().lock();
}

void ShopScene::draw()
{
	Scene::draw();
}

void ShopScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void ShopScene::loadData()
{
	mSceneHelper = std::make_unique<SceneHelper>(weak_from_this());

	loadUI();
	loadPlayer();
}

void ShopScene::loadUI()
{
	mShopHUD = std::make_shared<ShopHUD>(std::dynamic_pointer_cast<ShopScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	mShopHUD->initailize();

	auto game = getGame().lock();
	auto ui = std::make_shared<UI>(weak_from_this(), game->getRenderer());
	ui->initailize();
	ui->addButton([this]() {mSceneHelper->changeToTitleScene(mInfo); }, Vector2(500.0f, -300.0f), "Asset/Image/Button/HomeButton");
	ui->addButton([this]() {upgradeStatLevel(mInfo.mControlInfo.mHpLevel, "HP"); }, Vector2(-50.0f, 250.0f), "Asset/Image/Button/Upgrade");
	ui->addButton([this]() {upgradeStatLevel(mInfo.mControlInfo.mDefLevel, "DEF"); }, Vector2(-50.0f, 148.0f), "Asset/Image/Button/Upgrade");
	ui->addButton([this]() {upgradeStatLevel(mInfo.mControlInfo.mSpeedLevel, "SPEED"); }, Vector2(-50.0f, 46.0f), "Asset/Image/Button/Upgrade");
	ui->addButton([this]() {upgradeStatLevel(mInfo.mMinionInfo.mHpLevel, "HP"); }, Vector2(-50.0f, -56.0f), "Asset/Image/Button/Upgrade");
	ui->addButton([this]() {upgradeStatLevel(mInfo.mMinionInfo.mDefLevel, "DEF"); }, Vector2(-50.0f, -158.0f), "Asset/Image/Button/Upgrade");
	ui->addButton([this]() {upgradeStatLevel(mInfo.mMinionInfo.mSpeedLevel, "SPEED"); }, Vector2(-50.0f, -260.0f), "Asset/Image/Button/Upgrade");
	ui->addButton([this]() {changeSkin(mControl, mInfo.mControlInfo, false); }, Vector2(370.0f, 145.0f), "Asset/Image/Button/BackButton");
	ui->addButton([this]() {changeSkin(mControl, mInfo.mControlInfo, true); }, Vector2(555.0f, 145.0f), "Asset/Image/Button/NextButton");
	ui->addButton([this]() {changeSkin(mMinion, mInfo.mMinionInfo, false); }, Vector2(370.0f, -155.0f), "Asset/Image/Button/BackButton");
	ui->addButton([this]() {changeSkin(mMinion, mInfo.mMinionInfo, true); }, Vector2(555.0f, -155.0f), "Asset/Image/Button/NextButton");
}

void ShopScene::loadPlayer()
{
	mControl = std::make_shared<Player>(weak_from_this(), mInfo.mControlInfo);
	mControl->setScale(1.5f);
	mControl->setRotation(Quaternion(Vector3::UnitY, Math::Pi));
	mControl->setPosition(Vector3(17.0f, 3.0f, 0.0f));
	mControl->initailize();

	mMinion = std::make_shared<Player>(weak_from_this(), mInfo.mMinionInfo);
	mMinion->setScale(1.5f);
	mMinion->setRotation(Quaternion(Vector3::UnitY, Math::Pi));
	mMinion->setPosition(Vector3(17.0f, -27.0f, 0.0f));
	mMinion->initailize();
}

void ShopScene::unLoadData()
{

}

void ShopScene::upgradeStatLevel(int& statLevel, const std::string& type)
{
	auto isBuy = true;

	if (type == "HP")
	{
		if (statLevel == PlayerInfo::MAXHPLEVEL)
		{
			isBuy = false;
			//货肺款 UI积己
			mSceneHelper->createDialog("Upgrade");
		}
	}
	else if (type == "DEF")
	{
		if (statLevel == PlayerInfo::MAXDEFLEVEL)
		{
			isBuy = false;
			//货肺款 UI积己
			mSceneHelper->createDialog("Upgrade");
		}
	}
	else
	{
		if (statLevel == PlayerInfo::MAXSPEEDLEVEL)
		{
			isBuy = false;
			//货肺款 UI积己
			mSceneHelper->createDialog("Upgrade");
		}
	}

	if (isBuy)
	{
		statLevel++;
		mInfo.mCoin -= statLevel;
		mShopHUD->resetInfo();
	}
}

void ShopScene::changeSkin(std::shared_ptr<class Player>& player, PlayerInfo& info, bool next)
{
	info.changeSkinType(next);
	mControl->changePlayerTexture();
	mMinion->changePlayerTexture();
	player->setPlayerInfo(info);
	mControl->setPlayerTexture();
	mMinion->setPlayerTexture();
}