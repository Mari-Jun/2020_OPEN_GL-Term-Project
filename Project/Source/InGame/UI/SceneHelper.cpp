#include "SceneHelper.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Scene/Scene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/EditScene.h"
#include "../Scene/LoadingScene.h"
#include "../Scene/ShopScene.h"
#include "../Scene/SettingScene.h"
#include "../../Game/Sound/Sound.h"
#include "DialogUI.h"

SceneHelper::SceneHelper(const std::weak_ptr<class Scene>& scene)
	: mScene(scene)
{

}

SceneHelper::~SceneHelper()
{

}

void SceneHelper::changeToTitleScene(const GameInfo& info)
{
	mScene.lock()->getGame().lock()->getSound()->stopBgmChannel(0);
	auto scene = std::make_shared<TitleScene>(mScene.lock()->getGame(), info);
	scene->initailize();
	mScene.lock()->setSceneState(Scene::SceneState::Dead);
}

void SceneHelper::changeToGameScene(const GameInfo& info, int stage)
{
	auto scene = std::make_shared<GameScene>(mScene.lock()->getGame(), info, stage);
	scene->initailize();
	mScene.lock()->setSceneState(Scene::SceneState::Dead);
}

void SceneHelper::changeToEditScene(const GameInfo& info)
{
	auto scene = std::make_shared<EditScene>(mScene.lock()->getGame(), info, info.mStage);
	scene->initailize();
	mScene.lock()->setSceneState(Scene::SceneState::Dead);
}

void SceneHelper::changeToShopScene(const GameInfo& info)
{
	auto scene = std::make_shared<ShopScene>(mScene.lock()->getGame(), info);
	scene->initailize();
	mScene.lock()->setSceneState(Scene::SceneState::Dead);
}

void SceneHelper::changeToSettingScene(const GameInfo& info)
{
	auto scene = std::make_shared<SettingScene>(mScene.lock()->getGame(), info);
	scene->initailize();
	mScene.lock()->setSceneState(Scene::SceneState::Dead);
}

void SceneHelper::quitGame()
{
	mScene.lock()->setSceneState(Scene::SceneState::Dead);
	mScene.lock()->getGame().lock()->shutDown();
}

void SceneHelper::createDialog(const std::string& typeName)
{
	auto game = mScene.lock()->getGame().lock();
	auto ui = std::make_shared<DialogUI>(mScene, game->getRenderer());
	ui->initailize();
	ui->setBackgroundTexture(game->getRenderer()->getTexture("Asset/Image/UIBackground/" + typeName + ".png"));
}