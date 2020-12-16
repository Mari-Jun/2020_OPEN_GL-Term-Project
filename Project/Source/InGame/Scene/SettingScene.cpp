#include <string>
#include "SettingScene.h"
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
#include "../UI/HUD/SettingHUD.h"


SettingScene::SettingScene(const std::weak_ptr<class Game>& game, GameInfo info)
	: Scene(game)
	, mInfo(info)
{

}

SettingScene::~SettingScene()
{

}

void SettingScene::initailize()
{
	Scene::initailize();
	loadData();

	auto game = getGame().lock();

	//SetMouse
	game->getMouse()->setCursor(GLUT_CURSOR_INHERIT);
	game->getMouse()->setWarp(false);

	//Set View
	auto windowSize = getGame().lock()->getRenderer()->getWindow()->getSize();
	auto view = Matrix4::CreateSimpleViewProj(windowSize.x, windowSize.y);
	getGame().lock()->getRenderer()->setViewMatrix(view);

	//Set Sound
	game->getSound()->play(static_cast<int>(Sound::Type::bgm), static_cast<int>(Sound::bgmName::Edit), 0);
}

void SettingScene::sceneInput()
{
	Scene::sceneInput();

	auto game = getGame().lock();
}

void SettingScene::draw()
{
	Scene::draw();
}

void SettingScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void SettingScene::loadData()
{
	mSceneHelper = std::make_unique<SceneHelper>(weak_from_this());

	loadUI();
	
}

void SettingScene::loadUI()
{
	mSettingHUD = std::make_shared<SettingHUD>(std::dynamic_pointer_cast<SettingScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	mSettingHUD->initailize();


	auto game = getGame().lock();
	auto ui = std::make_shared<UI>(weak_from_this(), game->getRenderer());
	ui->initailize();
	ui->addButton([this]() {mSceneHelper->changeToTitleScene(mInfo); }, Vector2(-500.0f, -300.0f), "Asset/Image/Button/HomeButton");

	ui->addButton([this]() {
		getGame().lock()->getSound()->BGMvolumeUP();
		getGame().lock()->getSound()->play(static_cast<int>(Sound::Type::bgm), static_cast<int>(Sound::bgmName::Edit), 0);
	}, Vector2(320.0f, 70.0f), "Asset/Image/Button/UpButton");

	ui->addButton([this]() {
		getGame().lock()->getSound()->BGMvolumeDOWN();
		getGame().lock()->getSound()->play(static_cast<int>(Sound::Type::bgm), static_cast<int>(Sound::bgmName::Edit), 0);
	}, Vector2(180.0f, 70.0f), "Asset/Image/Button/DownButton");

	ui->addButton([this]() {getGame().lock()->getSound()->EFFECTvolumeUP(); }, Vector2(320.0f, -90.0f), "Asset/Image/Button/UpButton");
	ui->addButton([this]() {getGame().lock()->getSound()->EFFECTvolumeDOWN(); }, Vector2(180.0f, -90.0f), "Asset/Image/Button/DownButton");
}

void SettingScene::unLoadData()
{

}

void SettingScene::playGame(int stage)
{
	mSceneHelper->changeToGameScene(mInfo, stage);
}


