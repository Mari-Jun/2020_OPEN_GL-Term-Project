#include "SceneHelper.h"
#include "../../Game/Game.h"
#include "../../Game/Scene/Scene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/EditScene.h"
#include "NotYetUI.h"

SceneHelper::SceneHelper(const std::weak_ptr<class Scene>& scene)
	: mScene(scene)
{

}

SceneHelper::~SceneHelper()
{

}

void SceneHelper::changeToTitleScene()
{
	auto scene = std::make_shared<TitleScene>(mScene.lock()->getGame());
	scene->initailize();
	mScene.lock()->setState(Scene::State::Dead);
}

void SceneHelper::changeToGameScene()
{
	auto scene = std::make_shared<GameScene>(mScene.lock()->getGame());
	scene->initailize();
	mScene.lock()->setState(Scene::State::Dead);
}

void SceneHelper::changeToEditScene()
{
	auto scene = std::make_shared<EditScene>(mScene.lock()->getGame());
	scene->initailize();
	mScene.lock()->setState(Scene::State::Dead);
}

void SceneHelper::quitGame()
{
	mScene.lock()->setState(Scene::State::Dead);
	mScene.lock()->getGame().lock()->shutDown();
}

void SceneHelper::notYet()
{
	auto game = mScene.lock()->getGame().lock();
	auto ui = std::make_shared<NotYetUI>(mScene, game->getRenderer());
	ui->initailize();
}