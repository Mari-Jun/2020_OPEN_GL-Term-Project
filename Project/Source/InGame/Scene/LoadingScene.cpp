#include "LoadingScene.h"
#include "GameScene.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Sound/Sound.h"


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
	loadData();
}

void LoadingScene::sceneInput()
{

}

void LoadingScene::sceneUpdate(float deltatime)
{
	count += 1;

	auto game = getGame().lock();

	//Á¶°Ç
	if (count > 50)
	{
		game->getSound()->play(static_cast<int>(Sound::CHANNEL::bgm), static_cast<int>(Sound::bgmName::Game));
		auto scene = std::make_shared<GameScene>(getGame());
		scene->initailize();
		setState(State::Dead);
	}
}

void LoadingScene::loadData()
{

}

void LoadingScene::unLoadData()
{

}