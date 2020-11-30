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

}

void LoadingScene::sceneInput()
{

}

void LoadingScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);

	count += 1;

	auto game = getGame().lock();

	//Á¶°Ç
	if (count > 100)
	{

		getGame().lock()->releaseAllScene();
		setSceneState(SceneState::Dead);
	}
	
}

void LoadingScene::loadData()
{
	mLoadingHUD = std::make_shared<LoadingHUD>(std::dynamic_pointer_cast<LoadingScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	mLoadingHUD->initailize();
}

void LoadingScene::unLoadData()
{

}