#include "CameraActor.h"
#include "../../Graphics/Renderer/Renderer.h"
#include "../../Game.h"
#include "../../Input/KeyBoard.h"
#include "../../Input/Mouse.h"
#include "../../Component/MoveComponent.h"
#include "../../Camera/FPSMouseCamera.h"


CameraActor::CameraActor(const std::weak_ptr<class Scene>& scene)
	: Actor(scene)
	, mState(CameraState::Mouse)
{
	std::cerr << "Create CameraActor\n";
}

CameraActor::~CameraActor()
{
	std::cerr << "Destory CameraActor\n";
}

void CameraActor::initailize()
{
	Actor::initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create FPSCamera
	mFPSCamera = std::make_shared<FPSMouseCamera>(weak_from_this());
	mFPSCamera->initailize();
}

void CameraActor::updateActor(float deltatime)
{
	
}

void CameraActor::actorInput()
{
	if (mState == CameraState::Basic)
	{
		InputBasic();
	}
	else if (mState == CameraState::Mouse)
	{
		InputMouse();
	}

	auto game = getGame().lock();

	if (game->getKeyBoard()->isKeyPressed('1'))
	{
		mState = CameraState::Basic;
	}
	if (game->getKeyBoard()->isKeyPressed('2'))
	{
		mState = CameraState::Mouse;
	}
}

void CameraActor::InputBasic()
{
	auto game = getGame().lock();

	float forwardSpeed = 0.0f;
	float sideSpeed = 0.0f;
	float upSpeed = 0.0f;
	float angluarSpeed = 0.0f;

	if (game->getKeyBoard()->isKeyPressed('w'))
	{
		forwardSpeed = 100.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('s'))
	{
		forwardSpeed = -100.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('a'))
	{
		sideSpeed = -100.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('d'))
	{
		sideSpeed = 100.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('q'))
	{
		angluarSpeed = -Math::TwoPi / 5;
	}
	if (game->getKeyBoard()->isKeyPressed('e'))
	{
		angluarSpeed = Math::TwoPi / 5;
	}
	if (game->getKeyBoard()->isKeyPressed('v'))
	{
		upSpeed = -100.0f;
	}
	if (game->getKeyBoard()->isKeyPressed(32))
	{
		upSpeed = 100.0f;
	}

	mMoveComponent->setForwardSpeed(forwardSpeed);
	mMoveComponent->setSideSpeed(sideSpeed);
	mMoveComponent->setUpSpeed(upSpeed);
	mMoveComponent->setAngularSpeed(angluarSpeed);
}

void CameraActor::InputMouse()
{
	auto game = getGame().lock();

	float forwardSpeed = 0.0f;
	float upSpeed = 0.0f;
	float sideSpeed = 0.0f;

	//KeyBoard Move
	if (game->getKeyBoard()->isKeyPressed('w'))
	{
		forwardSpeed = 500.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('s'))
	{
		forwardSpeed = -500.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('a'))
	{
		sideSpeed = -500.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('d'))
	{
		sideSpeed = 500.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('v'))
	{
		upSpeed = -300.0f;
	}
	if (game->getKeyBoard()->isKeyPressed(32))
	{
		upSpeed = 300.0f;
	}

	mMoveComponent->setForwardSpeed(forwardSpeed);
	mMoveComponent->setSideSpeed(sideSpeed);
	mMoveComponent->setUpSpeed(upSpeed);

	float angluarSpeed = 0.0f;
	float pitchSpeed = 0.0f;

	//Mouse Rotate
	Vector2 mouseRelativePos = game->getMouse()->getPosition() - game->getMouse()->getOriginPosition();
	mouseRelativePos.y *= -1;

	if (mouseRelativePos.x != 0)
	{
		angluarSpeed = mouseRelativePos.x / 10.0f;
	}
	if (mouseRelativePos.y != 0)
	{
		pitchSpeed = mouseRelativePos.y / 10.0f;
	}

	mMoveComponent->setAngularSpeed(angluarSpeed);
	mFPSCamera->setPitchSpeed(pitchSpeed);
}