#include <string>
#include "TitleScene.h"
#include "GameScene.h"
#include "../../Game/Graphics/Window.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Input/Mouse.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"
#include "../../Game/Sound/Sound.h"



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


	if (game->getMouse()->getState(GLUT_LEFT_BUTTON) &&
		game->getMouse()->getFirst(GLUT_LEFT_BUTTON))
	{
	
	}
}

void TitleScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void TitleScene::loadData()
{

}

void TitleScene::unLoadData()
{

}