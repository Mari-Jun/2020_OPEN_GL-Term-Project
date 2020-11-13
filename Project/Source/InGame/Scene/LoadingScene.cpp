#include "LoadingScene.h"
#include "GameScene.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"


LoadingScene::LoadingScene(const std::weak_ptr<class Game>& game)
	: Scene(game)
	, count(0)
{

}

LoadingScene::~LoadingScene()
{

}

void LoadingScene::initailize()
{
	Scene::initailize();
}

void LoadingScene::sceneInput()
{

}

void LoadingScene::sceneUpdate(float deltatime)
{
	count += 1;

	//Á¶°Ç
	if (count > 50)
	{
		auto scene = std::make_shared<GameScene>(getGame());
		scene->initailize();
		scene->loadData();
		setState(State::Dead);
	}
}

void LoadingScene::loadData()
{

}

void LoadingScene::unLoadData()
{

}