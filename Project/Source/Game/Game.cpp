#include "Graphics/Renderer/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include "Etc/DeltaTime.h"
#include "Input/KeyBoard.h"
#include "Input/Mouse.h"
#include "Scene/Scene.h"
#include "Scene/GameScene.h"
#include "Game.h"


Game::Game()
	: mDeltaTime(nullptr)
	, mKeyBoard(nullptr)
	, mMouse(nullptr)
	, mIsRunning(true)
	, mIsPaused(false)
	, mIsUpdateActor(false)
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
	if (mRenderer == nullptr || !mRenderer->initailize(Vector2(0.0f, 0.0f), Vector2(1024.0f, 768.0f), "FrameWork"))
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

	//Create DeltaTime
	mDeltaTime = std::make_unique<DeltaTime>();
	if (mDeltaTime == nullptr)
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
	auto scene = std::make_unique<GameScene>(weak_from_this());
	mScene.push(std::move(scene));

	loadData();

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
	mScene.top()->unLoadData();
	if (mRenderer != nullptr)
	{
		mRenderer->shutDown();
	}
	exit(0);
}

void Game::loadData()
{
	mScene.top()->loadData();
}

void Game::unLoadData()
{
	clearScene();

	if (mRenderer != nullptr)
	{
		mRenderer->unLoadData();
	}
}

void Game::revertScene(std::unique_ptr<class Scene>&& scene)
{
	clearScene();
	pushScene(std::move(scene));
}

void Game::clearScene()
{
	while (!mScene.empty())
	{
		popScene();
	}
} 

void Game::pushScene(std::unique_ptr<class Scene>&& scene)
{
	mScene.emplace(std::move(scene));
}

void Game::popScene()
{
	if (!mScene.empty())
	{
		mScene.pop();
	}
}

void Game::addActor(const std::shared_ptr<Actor>& actor)
{
	mScene.top()->addActor(actor);
}

void Game::removeActor(const std::weak_ptr<Actor>& actor)
{
	mScene.top()->removeActor(actor);
}

void Game::processInput()
{
	if (mKeyBoard->isKeyPressed(27))
	{
		mIsRunning = false;
	}

	mScene.top()->sceneInput();
}

void Game::update()
{
	static int Fps = 0;
	static float time = 0.0f;
	float deltatime = mDeltaTime->getDeltaTime();

	if (deltatime >= 0.016f)
	{
		Fps++;
		time += deltatime;
		mDeltaTime->reset();

		if (time >= 1.0f)
		{
			time -= 1.0f;
			std::cout << "ÇÁ·¹ÀÓ : " << Fps << '\n';
			Fps = 0;
		}
		mScene.top()->sceneUpdate(deltatime);
	}
}

void Game::draw()
{
	mScene.top()->draw();
}