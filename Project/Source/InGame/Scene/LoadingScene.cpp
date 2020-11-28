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

	//Á¶°Ç
	if (count > 10)
	{
		GameInfo info = {};
		if (!info.loadGameInfo())
		{
			info = { 1, 123,
			{PlayerInfo::PlayerType::Control, PlayerInfo::SkinType::Man, 1, 1, 1},
			{PlayerInfo::PlayerType::Minion, PlayerInfo::SkinType::Robot, 1, 1, 1} };
		}

		auto scene = std::make_shared<TitleScene>(getGame(), info);
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