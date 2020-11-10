#include "LoadingScene.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "GameScene.h"


LoadingScene::LoadingScene(const std::weak_ptr<class Game>& game)
	: Scene(game)
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
	static int count = 0;

	count += 1;
	std::cout << count << std::endl;

	//Á¶°Ç
	if (count > 200)
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