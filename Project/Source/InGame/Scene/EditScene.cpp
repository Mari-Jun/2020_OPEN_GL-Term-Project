#include <string>
#include "EditScene.h"
#include "GameScene.h"
#include "../../Game/Graphics/Window.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Input/Mouse.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"
#include "../../Game/Sound/Sound.h"
#include "../../Game/UI/UI.h"

#include "../Actor/Tile/Tile.h"
#include "../Map/GameMap.h"
#include "../Map/Editer/MapEditor.h"
#include "../UI/SceneHelper.h"

EditScene::EditScene(const std::weak_ptr<class Game>& game, int stage)
	: Scene(game)
	, mStage(stage)
	, mSaveButtonPos(Vector2(500.0f, -350.0f))
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

	//Set Sound
	game->getSound()->play(static_cast<int>(Sound::CHANNEL::bgm), static_cast<int>(Sound::bgmName::Edit));
}

void EditScene::sceneInput()
{
	Scene::sceneInput();

	auto game = getGame().lock();

	if (game->getKeyBoard()->isSpecialKeyPressed(GLUT_KEY_F5))
	{
		setState(State::Dead);
		auto scene = std::make_shared<GameScene>(getGame(), mStage);
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
	mSceneHelper = std::make_unique<SceneHelper>(weak_from_this());

	//Create UI
	auto game = getGame().lock();
	auto ui = std::make_shared<UI>(weak_from_this(), game->getRenderer());
	ui->initailize();
	ui->addButton([this]() {mSceneHelper->createDialog("NotYet"); }, Vector2(500.0f, -190.0f), "Asset/Image/Button/NewButton");
	ui->addButton([this]() {
		(mGameMap->saveMap()) ? 
		mSceneHelper->createDialog("Complete") :
		mSceneHelper->createDialog("NoComplete"); 
		}, Vector2(500.0f, -300.0f), "Asset/Image/Button/SaveButton");
	ui->addButton([this]() {mSceneHelper->changeToTitleScene(); }, Vector2(-500.0f, -300.0f), "Asset/Image/Button/HomeButton");

	loadBoard();
	if (!loadGameMap())
	{
		std::cerr << "Error : Load Map\n";
	}
}

void EditScene::unLoadData()
{
	
}

bool EditScene::loadGameMap()
{
	auto newMap = std::make_shared<GameMap>(weak_from_this(), 30.0f);
	std::string fileName = "Asset/Map/Stage";
	fileName += std::to_string(mStage);
	fileName += ".txt";
	if (newMap->loadMap(fileName))
	{
		mGameMap.swap(newMap);
		mEditor = std::make_unique<MapEditor>(weak_from_this(), mGameMap);
		mEditor->setLeftBoardPos(mLeftBoardPos);
		mEditor->setLeftBoardTexSize(mLeftBoardTexSize);
		mEditor->setRightBoardPos(mRightBoardPos);
		mEditor->setRightBoardTexSize(mRightBoardTexSize);
		return true;
	}
	return false;	
}

void EditScene::loadBoard()
{
	//Create Left Board
	auto actor = std::make_shared<Actor>(weak_from_this());
	actor->setPosition(Vector3(-500.0f, 80.0f, 0.0f));
	actor->initailize();

	auto image = std::make_shared<SpriteComponent>(actor, getGame().lock()->getRenderer());
	image->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/EditScene/left_board.png"));
	image->initailize();

	mLeftBoardPos = Vector2(actor->getPosition().x - image->getTexWidth() / 2, actor->getPosition().y + image->getTexHeight() / 2);
	mLeftBoardTexSize = Vector2(image->getTexWidth(), image->getTexHeight());

	//Create Right Board
	actor = std::make_shared<Actor>(weak_from_this());
	actor->setPosition(Vector3(500.0f, 130.0f, 0.0f));
	actor->initailize();

	image = std::make_shared<SpriteComponent>(actor, getGame().lock()->getRenderer());
	image->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/EditScene/right_board.png"));
	image->initailize();

	mRightBoardPos = Vector2(actor->getPosition().x - image->getTexWidth() / 2, actor->getPosition().y + image->getTexHeight() / 2);
	mRightBoardTexSize = Vector2(image->getTexWidth(), image->getTexHeight());
}