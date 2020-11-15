#include "CameraActor.h"
#include "../../Graphics/Renderer/Renderer.h"
#include "../../Game.h"
#include "../../Input/KeyBoard.h"
#include "../../Input/Mouse.h"
#include "../../Component/MoveComponent.h"
#include "../../Camera/FPSMouseCamera.h"


CameraActor::CameraActor(const std::weak_ptr<class Game>& game)
	: Actor(game)
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
	if (game->getKeyBoard()->isKeyPressed('r'))
	{
		Vector3 dis = Vector3(0.0f, 0.0f, 200.0f) - getPosition();
		setPosition(getPosition() + dis);
		setPosition(getPosition() - Vector3::Transform(dis, Quaternion(Vector3::UnitY, Math::ToRadians(1))));
		setRotation(Quaternion::Concatenate(getRotation(), Quaternion(Vector3::UnitY, Math::ToRadians(1))));
	}

	mMoveComponent->setForwardSpeed(forwardSpeed);
	mMoveComponent->setSideSpeed(sideSpeed);
	mMoveComponent->setAngularSpeed(angluarSpeed);
}

void CameraActor::InputMouse()
{
	auto game = getGame().lock();

	float forwardSpeed = 0.0f;
	float sideSpeed = 0.0f;

	//KeyBoard Move
	if (game->getKeyBoard()->isKeyPressed('w'))
	{
		forwardSpeed = 300.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('s'))
	{
		forwardSpeed = -300.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('a'))
	{
		sideSpeed = -300.0f;
	}
	if (game->getKeyBoard()->isKeyPressed('d'))
	{
		sideSpeed = 300.0f;
	}

	mMoveComponent->setForwardSpeed(forwardSpeed);
	mMoveComponent->setSideSpeed(sideSpeed);

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