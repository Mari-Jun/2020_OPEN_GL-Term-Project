#include "LoadingScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Sound/Sound.h"
#include "../Info/GameInfo.h"

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

	//조건
	if (count > 10)
	{
		GameInfo ret = { 1, 5, {1,1,1}, {1,1,1} }; //나중에 게임 파일로 저장하고 불러와야함
		
		auto scene = std::make_shared<TitleScene>(getGame(), ret);
		scene->initailize();
		setSceneState(SceneState::Dead);
	}
}

void LoadingScene::loadData()
{

}

void LoadingScene::unLoadData()
{

}