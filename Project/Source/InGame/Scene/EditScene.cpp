#include "EditScene.h"
#include "GameScene.h"
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

#include "../Actor/Player/RobotActor.h"
#include "../Actor/Particle/ParticleCreater.h"
#include "../Actor/Tile/Tile.h"
#include "../Map/GameMap.h"
#include "../Map/Editer/MapEditor.h"


EditScene::EditScene(const std::weak_ptr<class Game>& game)
	: Scene(game)
{

}

EditScene::~EditScene()
{

}

void EditScene::initailize()
{
	Scene::initailize();
	loadData();

	auto game = getGame().lock();

	//SetMouse
	game->getMouse()->setCursor(GLUT_CURSOR_INHERIT);
	game->getMouse()->setWarp(false);

	//Set View
	auto windowSize = getGame().lock()->getRenderer()->getWindow()->getSize();
	auto view = Matrix4::CreateLookAt(Vector3::Zero + Vector3::UnitY * 1000.0f, Vector3::UnitY, Vector3::UnitZ);
	auto projection = Matrix4::CreateOrtho(windowSize.x, windowSize.y, 0.0f, 5000.0f);
	getGame().lock()->getRenderer()->setViewMatrix(view);
	getGame().lock()->getRenderer()->setProjectionMatrix(projection);
}

void EditScene::sceneInput()
{
	Scene::sceneInput();

	auto game = getGame().lock();

	if (game->getKeyBoard()->isKeyPressed('x'))
	{
		setState(State::Dead);
		auto scene = std::make_shared<GameScene>(getGame());
		scene->initailize();
	}
}

void EditScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void EditScene::loadData()
{
	loadGameMap();

	//Create Editor
	mEditor = std::make_unique<MapEditor>(getGame(), mGameMap);

	/*auto a = std::make_shared<Actor>(getGame());
	a->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
	a->setScale(0.1f);
	a->initailize();
	auto sc = std::make_shared<SpriteComponent>(a, getGame().lock()->getRenderer());
	sc->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Mesh/background.png"));
	sc->initailize();*/
}

void EditScene::unLoadData()
{

}

void EditScene::loadGameMap()
{
	mGameMap = std::make_shared<GameMap>(getGame(), 30.0f);
	mGameMap->loadMap("Asset/Map/Stage1.txt");


}