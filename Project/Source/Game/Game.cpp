#include "Graphics/Renderer/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include "Etc/DeltaTime.h"
#include "Input/KeyBoard.h"
#include "Input/Mouse.h"
#include "Actor/PlaneActor.h"
#include "Actor/Camera/CameraActor.h"
#include "Actor/Camera/FollowCameraActor.h"
#include "Actor/Robot/RobotActor.h"
#include "Actor/Sky/Weather/Cloud.h"
#include "Actor/Sky/Solor/Solor.h"
#include "Actor/Bulider/Building.h"
#include "Actor/Defualt/DefualtShape.h"
#include "Game.h"
#include "Graphics/Mesh/MeshComponent.h"
#include "Graphics/Texture/SpriteComponent.h"


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
	unLoadData();
	if (mRenderer != nullptr)
	{
		mRenderer->shutDown();
	}
	exit(0);
}

void Game::loadData()
{
	loadActorData();
	loadWorldBox();
}

void Game::unLoadData()
{
	while (!mActor.empty())
	{
		mActor.clear();
	}

	if (mRenderer != nullptr)
	{
		mRenderer->unLoadData();
	}
}

void Game::loadActorData()
{
	//Create ControlRobot
	auto robot = std::make_shared<RobotActor>(weak_from_this(), RobotActor::RobotState::Control);
	robot->initailize();

	//Create CameraActor
	/*mMouseCamera = std::make_shared<CameraActor>(weak_from_this());
	mMouseCamera->initailize();*/
	mFollowCamera = std::make_shared<FollowCameraActor>(weak_from_this(), robot);
	mFollowCamera->initailize();

	//Create pyramid
	auto pyramid = std::make_shared<DefualtShape>(weak_from_this(), DefualtShape::Shape::Pyramid);
	pyramid->setPosition(Vector3(0.0f, 70.0f, 400.0f));
	pyramid->setScale(200.0f);
	pyramid->setMeshColor(Vector3::Rgb(Vector3(229.0f, 216.0f, 92.0f)));
	pyramid->initailize();

	//Create Cloud
	auto cloud = std::make_shared<Cloud>(weak_from_this());
	cloud->setPosition(Vector3(0.0f, 500.0f, 400.0f));
	cloud->setScale(400.0f);
	cloud->initailize();

	//Create Solor
	auto solor = std::make_shared<Solor>(weak_from_this());
	solor->setPosition(Vector3(0.0f, 150.0f, 400.0f));
	solor->initailize();

	//Create Building
	auto buildings = std::make_shared<Building>(weak_from_this());
	buildings->setPosition(Vector3(0.0f, -50.0f, 400.0f));
	buildings->initailize();
}

void Game::loadWorldBox()
{
	//Create WorldBox
	std::shared_ptr<PlaneActor> plane = nullptr;
	Quaternion q;

	//Set floor
	plane = std::make_shared<PlaneActor>(weak_from_this());
	plane->setPosition(Vector3(0.0f, -30.0f, 400.0f));
	plane->setScale(500.0f);
	plane->initailize();
	plane->setTexture("Asset/Mesh/Road.png");

	auto a = std::make_shared<Actor>(weak_from_this());
	a->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
	a->setScale(0.1f);
	a->initailize();
	auto sc = std::make_shared<SpriteComponent>(a, mRenderer);
	sc->setTexture(mRenderer->getTexture("Asset/Mesh/background.png"));
	sc->initailize();
}

void Game::addActor(const std::shared_ptr<Actor>& actor)
{
	if (mIsUpdateActor)
	{
		mReadyActor.emplace_back(actor);
	}
	else
	{
		mActor.emplace_back(actor);
	}
}

void Game::removeActor(const std::weak_ptr<Actor>& actor)
{
	auto iter = std::find_if(mReadyActor.begin(), mReadyActor.end(),
		[&actor](const std::weak_ptr<Actor>& act)
		{return actor.lock() == act.lock(); });
	if (iter != mReadyActor.end())
	{
		std::iter_swap(iter, mReadyActor.end() - 1);
		mReadyActor.pop_back();
	}

	iter = std::find_if(mActor.begin(), mActor.end(),
		[&actor](const std::weak_ptr<Actor>& act)
		{return actor.lock() == act.lock(); });
	if (iter != mActor.end())
	{
		std::iter_swap(iter, mActor.end() - 1);
		mActor.pop_back();	
	}
}

void Game::addPlane(const std::shared_ptr<class PlaneActor>& plane)
{
	mPlaneActor.emplace_back(plane);
}

void Game::removePlane(const std::weak_ptr<class PlaneActor>& plane)
{
	auto iter = std::find_if(mPlaneActor.begin(), mPlaneActor.end(),
		[&plane](const std::weak_ptr<PlaneActor>& pAct)
		{return plane.lock() == pAct.lock(); });
	if (iter != mPlaneActor.end())
	{
		mPlaneActor.erase(iter);
	}
}

void Game::processInput()
{
	if (mKeyBoard->isKeyPressed(27))
	{
		mIsRunning = false;
	}

	mRenderer->processInput();

	mIsUpdateActor = true;
	for (auto actor : mActor)
	{
		actor->processInput();
	}
	mIsUpdateActor = false;
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

		mIsUpdateActor = true;
		for (auto actor : mActor)
		{
			actor->update(deltatime);
		}
		mIsUpdateActor = false;

		for (auto actor : mReadyActor)
		{
			actor->updateWorldTransform();
			mActor.emplace_back(actor);
		}
		mReadyActor.clear();

		std::vector<std::shared_ptr<Actor>> deadActor;
		for (auto& actor : mActor)
		{
			if (actor->getState() == Actor::State::Dead)
			{
				deadActor.emplace_back(std::move(actor));
			}
		}

		for (auto& actor : deadActor)
		{
			actor.reset();
		}
		deadActor.clear();

		mRenderer->update(deltatime);
	}


}

void Game::draw()
{
	mRenderer->draw();
}