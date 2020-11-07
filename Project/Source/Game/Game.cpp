#include "Graphics/Renderer/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include "Etc/DeltaTime.h"
#include "Input/KeyBoard.h"
#include "Input/Mouse.h"
#include "Actor/PlaneActor.h"
#include "Actor/CameraActor.h"
#include "Actor/CraneActor.h"
#include "Actor/Defualt/DefualtShape.h"
#include "Game.h"
#include "Graphics/Mesh/MeshComponent.h"


Game::Game()
	: mDeltaTime(nullptr)
	, mKeyBoard(nullptr)
	, mMouse(nullptr)
	, mIsRunning(true)
	, mIsPaused(false)
	, mIsUpdateActor(false)
	, mLightAni(false)
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
	//Create CameraActor
	mCameraActor = std::make_shared<CameraActor>(weak_from_this());
	mCameraActor->initailize();

	//Create PlaneActor //바닥만들기
	auto mPlaneActor = std::make_shared<PlaneActor>(weak_from_this());
	mPlaneActor->setPosition(Vector3(0.0f, -30.0f, 100.0f));
	mPlaneActor->setScale(100.0f);
	mPlaneActor->initailize();
	mPlaneActor->setPlaneColor(Vector3(0.8f, 0.8f, 0.8f));

	//Create CraneActor
	auto mCraneActor = std::make_shared<CraneActor>(weak_from_this());
	mCraneActor->setPosition(Vector3(0.0f, -28.0f, 100.0f));
	mCraneActor->initailize();

	//Create LightActor
	mLightActor = std::make_shared<DefualtShape>(weak_from_this());
	mLightActor->setPosition(Vector3(80.0f, 30.0f, 100.0f));
	mLightActor->setScale(10.0f);
	mLightActor->setMeshColor(Vector3(1.0f, 1.0f, 1.0f));
	mLightActor->initailize();
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

	if (mKeyBoard->isKeyPressed('r'))
	{
		mLightAni = true;
	}
	if (mKeyBoard->isKeyPressed('R'))
	{
		mLightAni = false;
	}

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
			std::cout << "프레임 : " << Fps << '\n';
			Fps = 0;
		}

		//Mouse Update
		mMouse->update();

		if (mLightAni)
		{
			mLightActor->setPosition(mLightActor->getPosition() - Vector3(0.0f, 0.0f, 100.0f));
			mLightActor->setPosition(Vector3::Transform(mLightActor->getPosition(), Quaternion(Vector3::UnitY, Math::ToRadians(-200.0f * deltatime))));
			mLightActor->setPosition(mLightActor->getPosition() + Vector3(0.0f, 0.0f, 100.0f));
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

				//Mouse Reset
		mMouse->resetMousePosition();

		//Renderer Update
		mRenderer->update(deltatime);
	}
}

void Game::draw()
{
	mRenderer->draw();
}