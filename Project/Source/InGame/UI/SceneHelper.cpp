#include "SceneHelper.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Scene/Scene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/EditScene.h"
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
	auto scene = std::make_shared<TitleScene>(mScene.lock()->getGame(), info);
	scene->initailize();
	mScene.lock()->setState(Scene::State::Dead);
}

void SceneHelper::changeToGameScene(const GameInfo& info)
{
	auto scene = std::make_shared<GameScene>(mScene.lock()->getGame(), info);
	scene->initailize();
	mScene.lock()->setState(Scene::State::Dead);
}

void SceneHelper::changeToEditScene(const GameInfo& info)
{
	auto scene = std::make_shared<EditScene>(mScene.lock()->getGame(), info);
	scene->initailize();
	mScene.lock()->setState(Scene::State::Dead);
}

void SceneHelper::quitGame()
{
	mScene.lock()->setState(Scene::State::Dead);
	mScene.lock()->getGame().lock()->shutDown();
}

void SceneHelper::createDialog(const std::string& typeName)
{
	auto game = mScene.lock()->getGame().lock();
	auto ui = std::make_shared<DialogUI>(mScene, game->getRenderer());
	ui->initailize();
	ui->setBackgroundTexture(game->getRenderer()->getTexture("Asset/Image/UIBackground/" + typeName + ".png"));
}