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
#include "../UI/HUD/EditHUD.h"

EditScene::EditScene(const std::weak_ptr<class Game>& game, GameInfo info)
	: Scene(game)
	, mInfo(info)
	, mStage(mInfo.mStage)
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
		GameInfo ret = mInfo;
		ret.mStage = mStage;

		setSceneState(SceneState::Dead);
		auto scene = std::make_shared<GameScene>(getGame(), ret);
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

	mEditor = std::make_unique<MapEditor>(std::dynamic_pointer_cast<EditScene>(weak_from_this().lock()));
	loadBoard("Left", Vector3(-500.0f, 80.0f, 0.0f));
	loadBoard("Right", Vector3(500.0f, 230.0f, 0.0f));
	loadBoard("Time", Vector3(500.0f, -30.0f, 0.0f));

	mEditHUD = std::make_shared<EditHUD>(std::dynamic_pointer_cast<EditScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	mEditHUD->initailize();

	if (!loadGameMap())
	{
		std::cerr << "Error : Load Map\n";
	}

	//Create UI
	auto game = getGame().lock();
	auto ui = std::make_shared<UI>(weak_from_this(), game->getRenderer());
	ui->initailize();
	ui->addButton([this]() {mGameMap->newMap(); }, Vector2(500.0f, -190.0f), "Asset/Image/Button/NewButton");
	ui->addButton([this]() {
		(mGameMap->saveMap()) ? 
		mSceneHelper->createDialog("Complete") :
		mSceneHelper->createDialog("NoComplete"); 
		}, Vector2(500.0f, -300.0f), "Asset/Image/Button/SaveButton");
	ui->addButton([this]() {mSceneHelper->changeToTitleScene(mInfo); }, Vector2(-500.0f, -300.0f), "Asset/Image/Button/HomeButton");

	auto wSize = getGame().lock()->getRenderer()->getWindow()->getSize();
	ui->addButton([this]() {mGameMap->setMinionCount(mGameMap->getMinionCount() - 1); mEditHUD->resetInfo(); }, Vector2(-220.0f, -wSize.y / 2 + 50.0f), "Asset/Image/Button/DownButton");
	ui->addButton([this]() {mGameMap->setMinionCount(mGameMap->getMinionCount() + 1); mEditHUD->resetInfo(); }, Vector2(220.0f, -wSize.y / 2 + 50.0f), "Asset/Image/Button/UpButton");
}

void EditScene::unLoadData()
{
	
}

bool EditScene::loadGameMap(const std::string& time)
{
	auto newMap = std::make_shared<GameMap>(weak_from_this(), 30.0f);
	std::string fileName = "Asset/Map/Stage";
	fileName += std::to_string(mStage);
	fileName += ".txt";
	if (newMap->loadMap(fileName, time))
	{
		mGameMap.swap(newMap);
		mEditor->setGameMap(mGameMap);
		mEditHUD->setGameMap(mGameMap);
		mEditHUD->resetInfo();
		return true;
	}
	return false;	
}

void EditScene::loadBoard(std::string&& name, Vector3&& position)
{
	std::string fileName = "Asset/Image/EditScene/" + name + "_board.png";
	//Create Left Board
	auto actor = std::make_shared<Actor>(weak_from_this());
	actor->setPosition(position);
	actor->initailize();

	auto image = std::make_shared<SpriteComponent>(actor, getGame().lock()->getRenderer());
	image->setTexture(getGame().lock()->getRenderer()->getTexture(fileName));
	image->initailize();

	auto pos = Vector2(actor->getPosition().x - image->getTexWidth() / 2, actor->getPosition().y + image->getTexHeight() / 2);
	auto size = Vector2(image->getTexWidth(), image->getTexHeight());

	mEditor->setBoard(name, pos, size);
}