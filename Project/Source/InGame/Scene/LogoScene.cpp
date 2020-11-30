#include "LogoScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Sound/Sound.h"
#include "../Info/GameInfo.h"

LogoScene::LogoScene(const std::weak_ptr<class Game>& game)
	: Scene(game)
	, count(0)
{

}

LogoScene::~LogoScene()
{

}

void LogoScene::initailize()
{
	Scene::initailize();
	loadData();
	std::weak_ptr<Renderer> Renderer = getGame().lock()->getRenderer();
	for (int i = 0; i < 30; ++i)
	{
		std::string filename = "Asset/Image/LoadingScene/frame-" + std::to_string(i) + ".png";
		Renderer.lock()->getTexture(filename);
	}

}

void LogoScene::sceneInput()
{

}

void LogoScene::sceneUpdate(float deltatime)
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

void LogoScene::loadData()
{

}

void LogoScene::unLoadData()
{

}