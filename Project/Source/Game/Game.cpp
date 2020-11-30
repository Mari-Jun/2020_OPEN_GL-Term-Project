#include <algorithm>
#include "Graphics/Renderer/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include "Input/KeyBoard.h"
#include "Input/Mouse.h"
#include "Scene/Scene.h"
#include "Game.h"
#include "../InGame/Scene/LogoScene.h"
#include "../InGame/Scene/LoadingScene.h"
#include "Sound/Sound.h"
#include "../InGame/UI/SceneHelper.h"


Game::Game()
	: mKeyBoard(nullptr)
	, mMouse(nullptr)
	, mIsRunning(true)
	, mIsPaused(false)
	, mIsUpdateScene(false)
{

}

Game::~Game()
{

}

bool Game::initialize(int argc, char** argv)
{
	glutInit(&argc, argv);

	//Create Renderer
	mRenderer = std::make_shared<Renderer>(weak_from_this());
	if (mRenderer == nullptr || !mRenderer->initailize(Vector2(1366.0f, 768.0f), "Cruelty Tower"))
	{
		std::cerr << "Error : Renderer initailization\n";
		return false;
	}

	//Create Physics Engine
	mPhysEngine = std::make_shared<PhysEngine>(weak_from_this());
	if (mPhysEngine == nullptr)
	{
		return false;
	}

	//Create KeyBoard
	mKeyBoard = std::make_unique<KeyBoard>();
	if (mKeyBoard == nullptr)
	{
		std::cerr << "Error : KeyBoard initailization\n";
		return false;
	}

	//Create Mouse
	mMouse = std::make_unique<Mouse>();
	if (mMouse == nullptr)
	{
		std::cerr << "Error : Mouse initailization\n";
		return false;
	}

	//Create Scene
	auto scene = std::make_shared<LoadingScene>(weak_from_this());
	scene->initailize();
	//scene->loadData();


	//Create Sound
	mSound = std::make_shared<Sound>();

	return true;
}

void Game::run()
{
	while (mIsRunning)
	{
		processInput();
		update();
		draw();
	}
}

void Game::shutDown()
{
	if (mRenderer != nullptr)
	{
		mRenderer->shutDown();
	}
	exit(0);
}

void Game::loadData()
{
	
}

void Game::unLoadData()
{
	clearScene();

	if (mRenderer != nullptr)
	{
		mRenderer->unLoadData();
	}
}

void Game::revertScene(const std::shared_ptr<class Scene>& scene)
{
	clearScene();
	addScene(scene);
}

void Game::clearScene()
{
	for (const auto& scene : mScene)
	{
		scene->setSceneState(Scene::SceneState::Dead);
	}
} 

void Game::addScene(const std::shared_ptr<class Scene>& scene)
{
	if (mIsUpdateScene)
	{
		mReadyScene.emplace_back(scene);
	}
	else
	{
		mScene.emplace_back(scene);
	}
}

void Game::removeScene(const std::weak_ptr<class Scene>& scene)
{
	auto iter = std::find_if(mReadyScene.begin(), mReadyScene.end(),
		[&scene](const std::weak_ptr<Scene>& sc)
		{return scene.lock() == sc.lock(); });
	if (iter != mReadyScene.end())
	{
		mReadyScene.erase(iter);
	}

	iter = std::find_if(mScene.begin(), mScene.end(),
		[&scene](const std::weak_ptr<Scene>& sc)
		{return scene.lock() == sc.lock(); });
	if (iter != mScene.end())
	{
		mScene.erase(iter);
	}
}

void Game::processInput()
{
	if (mKeyBoard->isSpecialKeyPressed(GLUT_KEY_F4))
	{
		mIsRunning = false;
	}

	mIsUpdateScene = true;
	for (auto scene : mScene)
	{
		scene->processInput();
	}
	mIsUpdateScene = false;
}

void Game::releaseAllScene()
{
	for (const auto& scene : mScene)
	{
		scene->setSceneState(Scene::SceneState::Active);
	}
}

void Game::update()
{
	mIsUpdateScene = true;
	for (const auto& scene : mScene)
	{
		scene->update();
	}
	mIsUpdateScene = false;

	for (const auto& scene : mReadyScene)
	{
		mScene.emplace_back(scene);
	}
	mReadyScene.clear();

	std::vector<std::shared_ptr<Scene>> deadScene;
	for (auto& scene : mScene)
	{
		if (scene->getSceneState() == Scene::SceneState::Dead)
		{
			deadScene.emplace_back(std::move(scene));
		}
	}

	for (auto& scene : deadScene)
	{
		scene.reset();
	}
	deadScene.clear();

	//Mouse, Keyboard Reset
	mMouse->update();
	mKeyBoard->update();
}

void Game::draw()
{
	for (const auto& scene : mScene)
	{
		scene->draw();
	}
}