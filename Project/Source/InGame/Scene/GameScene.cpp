#include "GameScene.h"
#include "LoadingScene.h"
#include "EditScene.h"
#include "../../Game/Graphics/Window.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Input/Mouse.h"
#include "../../Game/Actor/PlaneActor.h"
#include "../../Game/Actor/Camera/CameraActor.h"
#include "../../Game/Actor/Camera/FollowCameraActor.h"
#include "../../Game/Actor/Defualt/DefualtShape.h"
#include "../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"
#include "../../Game/Sound/Sound.h"

#include "../Actor/Player/Type/ControlPlayer.h"
#include "../Actor/Particle/ParticleCreater.h"
#include "../Actor/Tile/Tile.h"
#include "../Map/GameMap.h"


GameScene::GameScene(const std::weak_ptr<class Game>& game, int stage)
	: Scene(game)
	, mStage(stage)
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
		setState(State::Dead);
		auto scene = std::make_shared<LoadingScene>(getGame());
		scene->initailize();
	}
	if (game->getKeyBoard()->isSpecialKeyPressed(GLUT_KEY_F5))
	{
		setState(State::Dead);
		auto scene = std::make_shared<EditScene>(getGame(), mStage);
		scene->initailize();
	}
}

void GameScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void GameScene::loadData()
{
	loadGameMap();
	loadActorData();
}

void GameScene::unLoadData()
{

}

void GameScene::loadActorData()
{
	//Create ControlRobot
	auto control = std::make_shared<ControlPlayer>(weak_from_this());
	control->setScale(1.5f);
	control->setPosition(mGameMap->getStartPosition() + Vector3(0.0f, 100.0f, 0.0f));
	control->initailize();

	//Create CameraActor
	/*mMouseCamera = std::make_shared<CameraActor>(getGame());
	mMouseCamera->initailize();*/
	mFollowCamera = std::make_shared<FollowCameraActor>(weak_from_this(), control);
	mFollowCamera->initailize();

	//Create ParticleCreater
	auto particle = std::make_shared<ParticleCreater>(weak_from_this());
	particle->setPosition(control->getPosition());
	particle->setScale(300.0f);
	particle->initailize();
}

void GameScene::loadGameMap()
{
	mGameMap = std::make_shared<GameMap>(weak_from_this());
	std::string file = "Asset/Map/Stage";
	file += std::to_string(mStage);
	file += ".txt";
	mGameMap->loadMap(file);
}