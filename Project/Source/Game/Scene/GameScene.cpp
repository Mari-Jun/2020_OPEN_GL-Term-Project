#include "GameScene.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Actor/Actor.h"
#include "../Input/KeyBoard.h"
#include "LoadingScene.h"

#include "../Actor/PlaneActor.h"
#include "../Actor/Camera/CameraActor.h"
#include "../Actor/Camera/FollowCameraActor.h"
#include "../Actor/Robot/RobotActor.h"
#include "../Actor/Sky/Weather/Cloud.h"
#include "../Actor/Sky/Solor/Solor.h"
#include "../Actor/Bulider/Building.h"
#include "../Actor/Defualt/DefualtShape.h"
#include "../Graphics/Mesh/MeshComponent.h"
#include "../Graphics/Texture/SpriteComponent.h"


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

	//Create pyramid
	auto pyramid = std::make_shared<DefualtShape>(getGame(), DefualtShape::Shape::Pyramid);
	pyramid->setPosition(Vector3(0.0f, 70.0f, 400.0f));
	pyramid->setScale(200.0f);
	pyramid->setMeshColor(Vector3::Rgb(Vector3(229.0f, 216.0f, 92.0f)));
	pyramid->initailize();

	//Create Cloud
	auto cloud = std::make_shared<Cloud>(getGame());
	cloud->setPosition(Vector3(0.0f, 500.0f, 400.0f));
	cloud->setScale(400.0f);
	cloud->initailize();

	//Create Solor
	auto solor = std::make_shared<Solor>(getGame());
	solor->setPosition(Vector3(0.0f, 150.0f, 400.0f));
	solor->initailize();

	//Create Building
	auto buildings = std::make_shared<Building>(getGame());
	buildings->setPosition(Vector3(0.0f, -50.0f, 400.0f));
	buildings->initailize();
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

	auto a = std::make_shared<Actor>(getGame());
	a->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
	a->setScale(0.1f);
	a->initailize();
	auto sc = std::make_shared<SpriteComponent>(a, getGame().lock()->getRenderer());
	sc->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Mesh/background.png"));
	sc->initailize();
}