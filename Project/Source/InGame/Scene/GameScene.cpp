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

#include "../Actor/Player/RobotActor.h"
#include "../Actor/Particle/ParticleCreater.h"
#include "../Actor/Tile/Tile.h"
#include "../Map/GameMap.h"


GameScene::GameScene(const std::weak_ptr<class Game>& game)
	: Scene(game)
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
	if (game->getKeyBoard()->isKeyPressed('x'))
	{
		

		setState(State::Dead);
		auto scene = std::make_shared<EditScene>(getGame());
		game->getSound()->play(static_cast<int>(Sound::CHANNEL::bgm), static_cast<int>(Sound::Name::Edit));
		scene->initailize();
	}
}

void GameScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void GameScene::loadData()
{
	loadGameMap(1);
	loadActorData();
}

void GameScene::unLoadData()
{

}

void GameScene::loadActorData()
{
	//Create ControlRobot
	auto robot = std::make_shared<RobotActor>(weak_from_this());
	robot->setScale(1.5f);
	robot->setPosition(mGameMap->getStartPosition() + Vector3(0.0f, 100.0f, 0.0f));
	robot->initailize();

	//Create CameraActor
	/*mMouseCamera = std::make_shared<CameraActor>(getGame());
	mMouseCamera->initailize();*/
	mFollowCamera = std::make_shared<FollowCameraActor>(weak_from_this(), robot);
	mFollowCamera->initailize();

	////Create ParticleCreater
	//auto particle = std::make_shared<ParticleCreater>(getGame());
	//particle->setPosition(Vector3(0.0f, 500.0f, 400.0f));
	//particle->setScale(400.0f);
	//particle->initailize();
}

void GameScene::loadGameMap(int stage)
{
	mGameMap = std::make_shared<GameMap>(weak_from_this());
	std::string file = "Asset/Map/Stage";
	file += std::to_string(stage);
	file += ".txt";
	mGameMap->loadMap(file);
}