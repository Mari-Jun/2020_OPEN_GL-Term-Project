#include <string>
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
	, mStage(1)
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
	auto view = Matrix4::CreateLookAt(Vector3::UnitY * 10.0f, Vector3::Zero, Vector3::UnitZ);
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

	if (game->getKeyBoard()->isSpecialKeyPressed(GLUT_KEY_LEFT))
	{
		mStage--;
		if (!loadGameMap())
		{
			std::cerr << "Error : Load Map\n";
			mStage++;
		}
	}
	if (game->getKeyBoard()->isSpecialKeyPressed(GLUT_KEY_RIGHT))
	{
		mStage++;
		if (!loadGameMap())
		{
			std::cerr << "Error : Load Map\n";
			mStage--;
		}
	}

	mEditor->editInput();
}

void EditScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
}

void EditScene::loadData()
{
	if (!loadGameMap())
	{
		std::cerr << "Error : Load Map\n";
	}
	loadBoard();
}

void EditScene::unLoadData()
{
	
}

bool EditScene::loadGameMap()
{
	mGameMap = std::make_shared<GameMap>(getGame(), 30.0f);
	std::string fileName = "Asset/Map/Stage";
	fileName += std::to_string(mStage);
	fileName += ".txt";
	if (mGameMap->loadMap(fileName))
	{
		mEditor = std::make_unique<MapEditor>(getGame(), mGameMap);
		return true;
	}
	return false;	
}

void EditScene::loadBoard()
{
	auto leftBoard = std::make_shared<Actor>(getGame());
	leftBoard->setPosition(Vector3(-500.0f, 0.0f, 0.0f));
	leftBoard->initailize();

	//Create Left Board
	auto left = std::make_shared<SpriteComponent>(leftBoard, getGame().lock()->getRenderer());
	left->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/EditScene/left_board.png"));
	left->initailize();	

	mEditor->setLeftBoardPos(Vector2(leftBoard->getPosition().x - left->getTexWidth() / 2, left->getTexHeight() / 2));
	mEditor->setLeftBoardTexSize(Vector2(left->getTexWidth(), left->getTexHeight()));
}