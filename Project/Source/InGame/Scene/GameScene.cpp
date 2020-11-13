#include "GameScene.h"
#include "LoadingScene.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Actor/PlaneActor.h"
#include "../../Game/Actor/Camera/CameraActor.h"
#include "../../Game/Actor/Camera/FollowCameraActor.h"
#include "../../Game/Actor/Defualt/DefualtShape.h"
#include "../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"

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
		scene->loadData();
	}
}

void GameScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void GameScene::loadData()
{
	loadActorData();
	loadWorldBox();
	loadGameMap();
}

void GameScene::unLoadData()
{

}

void GameScene::loadActorData()
{
	//Create ControlRobot
	auto robot = std::make_shared<RobotActor>(getGame());
	robot->setScale(1.5f);
	robot->initailize();

	//Create CameraActor
	/*mMouseCamera = std::make_shared<CameraActor>(getGame());
	mMouseCamera->initailize();*/
	mFollowCamera = std::make_shared<FollowCameraActor>(getGame(), robot);
	mFollowCamera->initailize();

	//Create ParticleCreater
	auto particle = std::make_shared<ParticleCreater>(getGame());
	particle->setPosition(Vector3(0.0f, 500.0f, 400.0f));
	particle->setScale(400.0f);
	particle->initailize();
}

void GameScene::loadWorldBox()
{
	//Create WorldBox
	std::shared_ptr<PlaneActor> plane = nullptr;
	Quaternion q;

	//Set floor
	plane = std::make_shared<PlaneActor>(getGame());
	plane->setPosition(Vector3(0.0f, -30.0f, 400.0f));
	plane->setScale(500.0f);
	plane->initailize();
	plane->setTexture("Asset/Mesh/Road.png");

	/*auto a = std::make_shared<Actor>(getGame());
	a->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
	a->setScale(0.1f);
	a->initailize();
	auto sc = std::make_shared<SpriteComponent>(a, getGame().lock()->getRenderer());
	sc->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Mesh/background.png"));
	sc->initailize();*/
}

void GameScene::loadGameMap()
{
	mGameMap = std::make_shared<GameMap>(getGame());
	mGameMap->loadMap("Asset/Map/Stage1.txt");
}