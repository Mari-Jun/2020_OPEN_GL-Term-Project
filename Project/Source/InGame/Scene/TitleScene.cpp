#include <string>
#include "TitleScene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "../../Game/Graphics/Window.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Input/Mouse.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"
#include "../../Game/Sound/Sound.h"
#include "../../Game/UI/UI.h"



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
	//Create UI
	auto ui = std::make_shared<UI>(weak_from_this(), getGame().lock()->getRenderer());
	ui->initailize();
	auto texture = getGame().lock()->getRenderer()->getTexture("Asset/Image/TitleScene/PlayButton.png");
	ui->addButton([this]() {changeToGameScene(); }, Vector2(0.0f, 0.0f), texture);
	texture = getGame().lock()->getRenderer()->getTexture("Asset/Image/TitleScene/EditButton.png");
	ui->addButton([this]() {changeToEditScene(); }, Vector2(0.0f, -150.0f), texture);
	texture = getGame().lock()->getRenderer()->getTexture("Asset/Image/TitleScene/QuitButton.png");
	ui->addButton([this]() {quitGame(); }, Vector2(0.0f, -300.0f), texture);
}

void TitleScene::unLoadData()
{

}

void TitleScene::changeToGameScene()
{
	auto scene = std::make_shared<GameScene>(getGame());
	scene->initailize();
	setState(State::Dead);
}

void TitleScene::changeToEditScene()
{
	setState(State::Dead);
	auto scene = std::make_shared<EditScene>(getGame(), mStage);
	scene->initailize();
}

void TitleScene::quitGame()
{
	setState(State::Dead);
	getGame().lock()->shutDown();
}