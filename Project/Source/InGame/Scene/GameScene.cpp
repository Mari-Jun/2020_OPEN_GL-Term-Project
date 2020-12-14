//∞‘¿”æ¿.cpp
#include "GameScene.h"
#include "LoadingScene.h"
#include "EditScene.h"
#include "../../Game/Graphics/Window.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Graphics/Mesh/CubeMapComponent.h"
#include "../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"
#include "../../Game/Graphics/Mesh/Mesh.h"
#include "../../Game/Game.h"
#include "../../Game/Actor/Actor.h"
#include "../../Game/Input/KeyBoard.h"
#include "../../Game/Input/Mouse.h"
#include "../../Game/Actor/Camera/CameraActor.h"
#include "../../Game/Actor/Camera/FollowCameraActor.h"
#include "../../Game/Sound/Sound.h"

//#include "../Minimap/GameMinimap.h"
#include "../Minimap/GameMinimap.h"

#include "../Actor/CubeMap/CubeMap.h"
#include "../Actor/Player/Type/ControlPlayer.h"
#include "../Actor/Particle/ParticleCreator.h"
#include "../Actor/Player/Type/MinionAi/MinionManager.h"
#include "../Actor/Tile/Tile.h"
#include "../Map/GameMap.h"
#include "../UI/HUD/GameHUD.h"
#include "../UI/PauseUI.h"
#include "../UI/SceneHelper.h"

GameScene::GameScene(const std::weak_ptr<class Game>& game, GameInfo info, int stage)
	: Scene(game)
	, mInfo(info)
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
	auto projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), windowSize.x, windowSize.y, 1.0f, 3000.0f);
	game->getRenderer()->setProjectionMatrix(projection);

	//real cubemap
	mCubeMaps = std::make_shared<CubeMaps>(game->getRenderer(), mGameMap->getTime());
	mCubeMaps->initailize();

	//Set Sound
	game->getSound()->play(static_cast<int>(Sound::Type::bgm), mGameMap->getTimeBgm(), 0);

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
		auto scene = std::make_shared<EditScene>(getGame(), mInfo, mStage);
		scene->initailize();
	}
	if (game->getKeyBoard()->isKeyFirst('p'))
	{
		if (mPhotoCamera->getState() == Actor::State::Active)
		{
			changePhotoToGame();
		}
		else
		{
			changeGameToPhoto();
		}
	}
	if (game->getKeyBoard()->isKeyFirst('+'))
	{
		getGame().lock()->getSound()->EFFECTvolumeUP();
	}
	if (game->getKeyBoard()->isKeyFirst('-'))
	{
		getGame().lock()->getSound()->EFFECTvolumeDOWN();
	}
	if (game->getKeyBoard()->isKeyFirst(VK_TAB))
	{
		mGameMinimap->OnOffMinimap();
	}
	if (game->getKeyBoard()->isKeyPressed(27))
	{
		pauseGame("Pause");
	}
}

void GameScene::draw()
{

	if (mGameMinimap->getMinimapEnable())
	{
		auto game = getGame().lock();
		auto windowSize = game->getRenderer()->getWindow()->getSize();
		Matrix4 play_view = game->getRenderer()->getViewMatrix();
		Matrix4 projection;

		//Draw Game
		game->getRenderer()->setEnableSwapBuffer(FALSE);

		//set Game Viewport
		glViewport(0, 0, windowSize.x, windowSize.y);
		projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), windowSize.x, windowSize.y, 1.0f, 3000.0f);
		game->getRenderer()->setProjectionMatrix(projection);

		Scene::draw();

		//Draw Minimap
		//set minimap viewport
		glViewport(windowSize.x - 250, 0, 250, 250);

		auto minimapSize = Vector2(windowSize.x, windowSize.y);
		auto miniMapEye = mControl->getPosition();
		miniMapEye.y *= 2;
		//mMarker->setSpritePosition(Vector3::Zero);
		auto view = Matrix4::CreateLookAt(miniMapEye, mControl->getPosition(), mFollowCamera->getForward());
		//auto view = Matrix4::CreateLookAt(Vector3::UnitY * 100, Vector3::Zero, Vector3::UnitZ);
		//auto view = Matrix4::CreateLookAt(miniMapEye, mControl->getPosition(), Vector3::UnitX);
		projection = Matrix4::CreateOrtho(1000, 1000, 0.0f, 1000.0f);
		game->getRenderer()->setViewMatrix(view);
		game->getRenderer()->setProjectionMatrix(projection);
		game->getRenderer()->draw2();


		game->getRenderer()->setEnableSwapBuffer(TRUE);
		game->getRenderer()->setViewMatrix(play_view);
		game->getRenderer()->setProjectionMatrix(Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), windowSize.x, windowSize.y, 1.0f, 3000.0f));
		glViewport(0, 0, windowSize.x, windowSize.y);
	}
	else {
		Scene::draw();
	}


}

void GameScene::sceneUpdate(float deltatime)
{
	Scene::sceneUpdate(deltatime);
	getGame().lock()->getSound()->updateSound();

	//std::cout << mControl->getPosition().x << "," << mControl->getPosition().y << "," << mControl->getPosition().z << std::endl;
}

void GameScene::loadData()
{
	mSceneHelper = std::make_unique<SceneHelper>(weak_from_this());

	loadGameMap();
	loadActorData();
	loadUI();
	getGame().lock()->getSound()->setEffectIndex(mGameMap->getAttackTowerCount());

}

void GameScene::unLoadData()
{

}

void GameScene::loadActorData()
{
	//Create ControlRobot
	mControl = std::make_shared<ControlPlayer>(weak_from_this(), mInfo.mControlInfo);
	mControl->setScale(1.5f);
	mControl->setPosition(mGameMap->getStartPosition() + Vector3(0.0f, 100.0f, 0.0f));
	mControl->initailize();


	//Create CameraActor
	mFollowCamera = std::make_shared<FollowCameraActor>(weak_from_this(), mControl);
	mFollowCamera->initailize();

	mPhotoCamera = std::make_shared<CameraActor>(weak_from_this());
	mPhotoCamera->setPosition(Vector3(0.0f, 100.0f, 0.0f));
	mPhotoCamera->initailize();
	mPhotoCamera->setState(Actor::State::Paused);

	//Create ParticleCreator
	mParticle = std::make_shared<ParticleCreator>(weak_from_this(), mControl);
	mParticle->setScale(1000.0f);
	mParticle->setPosition(mControl->getPosition() + Vector3::UnitY * 300.0f);
	mParticle->initailize();

	//Create MinionManager
	mMinionManager = std::make_shared<MinionManager>(weak_from_this(), mGameMap, mInfo.mMinionInfo);
	mMinionManager->initailize();

	//Create Minimap Boundary
	mGameMinimap = std::make_shared<GameMinimap>(weak_from_this(), getGame().lock()->getRenderer(), mControl);
	mGameMinimap->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/Minimap/boundary.png"));
	mGameMinimap->initailize();
	mGameMinimap->setTexSize(1366, 768);


}

void GameScene::loadGameMap()
{
	mGameMap = std::make_shared<GameMap>(weak_from_this());
	std::string file = "Asset/Map/Stage";
	file += std::to_string(mStage);
	file += ".txt";
	mGameMap->loadMap(file);
}

void GameScene::loadUI()
{
	mGameHUD = std::make_shared<GameHUD>(std::dynamic_pointer_cast<GameScene>(weak_from_this().lock()), getGame().lock()->getRenderer());
	mGameHUD->initailize();
}

void GameScene::pauseGame(const std::string& type)
{
	//Create PauseUI
	auto game = getGame().lock();
	std::shared_ptr<class PauseUI> ui;
	if (type == "Pause")
	{
		ui = std::make_shared<PauseUI>(weak_from_this(), game->getRenderer());
	}
	else if (type == "Clear")
	{
		ui = std::make_shared<PauseUI>(weak_from_this(), game->getRenderer(), PauseUI::UIType::Clear);
	}
	else if (type == "Fail")
	{
		ui = std::make_shared<PauseUI>(weak_from_this(), game->getRenderer(), PauseUI::UIType::Fail);
	}
	ui->initailize();

	std::string fileName = "Asset/Image/UIBackground/" + type + ".png";

	ui->setBackgroundTexture(game->getRenderer()->getTexture(fileName));

	game->getMouse()->setCursor(GLUT_CURSOR_INHERIT);
	game->getMouse()->setWarp(false);
}

void GameScene::changeGameToPhoto()
{
	pauseAllActor();
	mPhotoCamera->setState(Actor::State::Active);
	mGameHUD->setIsPhoto(true);
}

void GameScene::changePhotoToGame()
{
	activeAllActor();
	mPhotoCamera->setState(Actor::State::Paused);
	mGameHUD->setIsPhoto(false);
}

void GameScene::stageClear()
{
	if (mMinionManager->getClearMinion() == 0)
	{
		pauseGame("Clear");

		mInfo.mCoin += mStage * 10;
		mInfo.mStage = Math::Max(mStage + 1, mInfo.mStage);
	}
}

void GameScene::stageFail()
{
	pauseGame("Fail");
}

void GameScene::goToTitle()
{
	//getGame().lock()->getSound()->stopBgmChannel(0);
	mSceneHelper->changeToTitleScene(mInfo);
}