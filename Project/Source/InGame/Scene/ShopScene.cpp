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

void ShopScene::sceneInput()
{
	Scene::sceneInput();

	auto game = getGame().lock();
}

void ShopScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void ShopScene::loadData()
{
	mSceneHelper = std::make_unique<SceneHelper>(weak_from_this());

	loadUI();
}

void ShopScene::loadUI()
{
	auto gameHUD = std::make_shared<ShopHUD>(std::dynamic_pointer_cast<ShopScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	gameHUD->initailize();

	auto game = getGame().lock();
	auto ui = std::make_shared<UI>(weak_from_this(), game->getRenderer());
	ui->initailize();
	ui->addButton([this]() {mSceneHelper->changeToTitleScene(mInfo); }, Vector2(500.0f, -300.0f), "Asset/Image/Button/HomeButton");
}

void ShopScene::unLoadData()
{

}