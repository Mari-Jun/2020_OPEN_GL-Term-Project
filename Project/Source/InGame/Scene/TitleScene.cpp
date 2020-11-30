#include <string>
#include "TitleScene.h"
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
#include "../UI/HUD/StageHUD.h"


TitleScene::TitleScene(const std::weak_ptr<class Game>& game, GameInfo info)
	: Scene(game)
	, mInfo(info)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::initailize()
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
	game->getSound()->play(static_cast<int>(Sound::Type::bgm), static_cast<int>(Sound::bgmName::main), 0);
}

void TitleScene::sceneInput()
{
	Scene::sceneInput();

	auto game = getGame().lock();
}

void TitleScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void TitleScene::loadData()
{
	mSceneHelper = std::make_unique<SceneHelper>(weak_from_this());

	//Create UI
	auto game = getGame().lock();
	auto ui = std::make_shared<UI>(weak_from_this(), game->getRenderer());
	ui->initailize();
	ui->setBackgroundTexture(game->getRenderer()->getTexture("Asset/Image/TitleScene/background.png"));
	ui->addButton([this]() {selectStage(); }, Vector2(0.0f, 30.0f), "Asset/Image/Button/PlayButton");
	ui->addButton([this]() {
		mInfo.saveGameInfo() ?
		mSceneHelper->createDialog("Complete") :
		mSceneHelper->createDialog("NoComplete"); 
		}, Vector2(0.0f, -80.0f), "Asset/Image/Button/SaveButton");
	ui->addButton([this]() {mSceneHelper->createDialog("NotYet"); }, Vector2(0.0f, -190.0f), "Asset/Image/Button/HelpButton");
	ui->addButton([this]() {mSceneHelper->quitGame(); }, Vector2(0.0f, -300.0f), "Asset/Image/Button/QuitButton");
	ui->addButton([this]() {mSceneHelper->changeToEditScene(mInfo); }, Vector2(500.0f, -300.0f), "Asset/Image/Button/EditButton");
	ui->addButton([this]() {mSceneHelper->changeToShopScene(mInfo); }, Vector2(-500.0f, -300.0f), "Asset/Image/Button/ShopButton");
}

void TitleScene::unLoadData()
{

}

void TitleScene::playGame(int stage)
{
	mSceneHelper->changeToGameScene(mInfo, stage);
}

void TitleScene::selectStage()
{
	//Create StageUI
	auto game = getGame().lock();
	auto ui =  std::make_shared<StageHUD>(weak_from_this(), game->getRenderer(), mInfo);
	ui->initailize();

	std::string fileName = "Asset/Image/UIBackground/Select.png";
	ui->setBackgroundTexture(game->getRenderer()->getTexture(fileName));

	game->getMouse()->setCursor(GLUT_CURSOR_INHERIT);
	game->getMouse()->setWarp(false);
}

