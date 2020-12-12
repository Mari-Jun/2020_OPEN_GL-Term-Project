#include <sstream>
#include <fstream>
#include <cmath>
#include "LoadingScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Sound/Sound.h"
#include "../Info/GameInfo.h"
#include "../UI/HUD/LoadingHUD.h"

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
	loadtexture();
}

void LoadingScene::sceneInput()
{

}

void LoadingScene::draw()
{
	Scene::draw();
}

void LoadingScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);

	//count += 1;

	auto game = getGame().lock();

	//Á¶°Ç
	//if (count > 100)
	//{
	//	//getGame().lock()->releaseAllScene();
	//	setSceneState(SceneState::Dead);
	//}

	std::weak_ptr<Renderer> mRender = getGame().lock()->getRenderer();
	if (!mLoader.empty())
	{
		if (mLoader[loadercount].find("png") != std::string::npos)
			mRender.lock()->loadTexture(mLoader[loadercount]);
		else
			mRender.lock()->loadMesh(mLoader[loadercount]);

		loadercount++;
	}
	if (loadercount == mLoader.size())
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
		loadercount = 0;
	}
	
}

void LoadingScene::loadData()
{
	mLoadingHUD = std::make_shared<LoadingHUD>(std::dynamic_pointer_cast<LoadingScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	mLoadingHUD->initailize();

}

bool LoadingScene::loadtexture()
{
	std::string fileName = "Asset/Image/imagefile.txt";

	std::ifstream mapFile(fileName);

	if (!mapFile.is_open())
	{
		std::cerr << "file not found : " << fileName << '\n';
		return false;
	}
	std::weak_ptr<Renderer> mRender = getGame().lock()->getRenderer();
	std::string line = "";

	while (std::getline(mapFile, line))
	{
		mLoader.push_back(line);

	}

	std::cerr << fileName << " load complete\n";

	return true;
}

void LoadingScene::unLoadData()
{

}