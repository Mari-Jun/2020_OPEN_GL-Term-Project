#include "GameScene.h"
#include "LoadingScene.h"
#include "EditScene.h"
#include "../../Game/Graphics/Window.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Input/Mouse.h"
#include "../../Game/Actor/Camera/CameraActor.h"
#include "../../Game/Actor/Camera/FollowCameraActor.h"
#include "../../Game/Sound/Sound.h"

#include "../Actor/Player/Type/ControlPlayer.h"
#include "../Actor/Particle/ParticleCreator.h"
#include "../Actor/Player/Type/MinionAi/MinionManager.h"
#include "../Actor/Tile/Tile.h"
#include "../Map/GameMap.h"
#include "../UI/HUD/GameHUD.h"
#include "../UI/PauseUI.h"
#include "../UI/SceneHelper.h"

GameScene::GameScene(const std::weak_ptr<class Game>& game, GameInfo info)
	: Scene(game)
	, mInfo(info)
{

}

GameScene::~GameScene()
{
	
}

void GameScene::initailize()
{
	Scene::initailize();
	loadData();

	auto game = getGame().lock();

	//SetMouse
	game->getMouse()->setCursor(GLUT_CURSOR_NONE);
	game->getMouse()->setWarp(true);

	//Set View
	auto windowSize = game->getRenderer()->getWindow()->getSize();
	auto projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), windowSize.x, windowSize.y, 25.0f, 1000.0f);
	game->getRenderer()->setProjectionMatrix(projection);

	//Set Sound
	game->getSound()->play(static_cast<int>(Sound::CHANNEL::bgm), static_cast<int>(Sound::bgmName::Game));
}

void GameScene::sceneInput()
{
	Scene::sceneInput();

	auto game = getGame().lock();

	if (game->getKeyBoard()->isKeyPressed('z'))
	{
		setSceneState(SceneState::Dead);
		auto scene = std::make_shared<LoadingScene>(getGame());
		scene->initailize();
	}
	if (game->getKeyBoard()->isSpecialKeyPressed(GLUT_KEY_F5))
	{
		setSceneState(SceneState::Dead);
		auto scene = std::make_shared<EditScene>(getGame(), mInfo);
		scene->initailize();
	}
	if (game->getKeyBoard()->isKeyPressed(27))
	{
		pauseGame();
	}
}

void GameScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void GameScene::loadData()
{
	mSceneHelper = std::make_unique<SceneHelper>(weak_from_this());

	loadGameMap();
	loadActorData();
	loadUI();
}

void GameScene::unLoadData()
{

}

void GameScene::loadActorData()
{
	//Create ControlRobot
	auto control = std::make_shared<ControlPlayer>(weak_from_this(), mInfo.mControlInfo);
	control->setScale(1.5f);
	control->setPosition(mGameMap->getStartPosition() + Vector3(0.0f, 100.0f, 0.0f));
	control->initailize();

	//Create CameraActor
	mFollowCamera = std::make_shared<FollowCameraActor>(weak_from_this(), control);
	mFollowCamera->initailize();
	/*auto mCamera = std::make_shared<CameraActor>(weak_from_this());
	mCamera->initailize();*/

	//Create ParticleCreator
	auto particle = std::make_shared<ParticleCreator>(weak_from_this(), control);
	particle->setScale(1000.0f);
	particle->setPosition(control->getPosition() + Vector3::UnitY * 300.0f);
	particle->initailize();

	//Create MinionManager
	mMinionManager = std::make_shared<MinionManager>(weak_from_this(), mGameMap, mInfo.mMinionInfo);
	mMinionManager->initailize();
}

void GameScene::loadGameMap()
{
	mGameMap = std::make_shared<GameMap>(weak_from_this());
	std::string file = "Asset/Map/Stage";
	file += std::to_string(mInfo.mStage);
	file += ".txt";
	mGameMap->loadMap(file);
}

void GameScene::loadUI()
{
	mGameHUD = std::make_shared<GameHUD>(std::dynamic_pointer_cast<GameScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	mGameHUD->initailize();
}

void GameScene::pauseGame()
{
	//Create PauseUI
	auto game = getGame().lock();
	auto ui = std::make_shared<PauseUI>(weak_from_this(), game->getRenderer());
	ui->initailize();
	ui->setBackgroundTexture(game->getRenderer()->getTexture("Asset/Image/UIBackground/Pause.png"));

	game->getMouse()->setCursor(GLUT_CURSOR_INHERIT);
	game->getMouse()->setWarp(false);
}

void GameScene::stageClear()
{
	//Create PauseUI
	auto game = getGame().lock();
	auto ui = std::make_shared<PauseUI>(weak_from_this(), game->getRenderer(), PauseUI::UIType::Clear);
	ui->initailize();
	ui->setBackgroundTexture(game->getRenderer()->getTexture("Asset/Image/UIBackground/StageClear.png"));

	game->getMouse()->setCursor(GLUT_CURSOR_INHERIT);
	game->getMouse()->setWarp(false);

	mInfo.mCoin += mInfo.mStage * 10;
	mInfo.mStage++;
}

void GameScene::goToTitle()
{
	mSceneHelper->changeToTitleScene(mInfo);
}