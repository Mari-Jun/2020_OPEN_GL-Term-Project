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


TitleScene::TitleScene(const std::weak_ptr<class Game>& game, int stage)
	: Scene(game)
	, mStage(stage)
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
	ui->addButton([this]() {mSceneHelper->changeToGameScene(); }, Vector2(0.0f, 30.0f), "Asset/Image/Button/PlayButton");
	ui->addButton([this]() {mSceneHelper->createDialog("NotYet"); }, Vector2(0.0f, -80.0f), "Asset/Image/Button/SaveButton");
	ui->addButton([this]() {mSceneHelper->createDialog("NotYet"); }, Vector2(0.0f, -190.0f), "Asset/Image/Button/HelpButton");
	ui->addButton([this]() {mSceneHelper->quitGame(); }, Vector2(0.0f, -300.0f), "Asset/Image/Button/QuitButton");
	ui->addButton([this]() {mSceneHelper->changeToEditScene(); }, Vector2(500.0f, -300.0f), "Asset/Image/Button/EditButton");
	ui->addButton([this]() {mSceneHelper->createDialog("NotYet"); }, Vector2(-500.0f, -300.0f), "Asset/Image/Button/ShopButton");
}

void TitleScene::unLoadData()
{

}