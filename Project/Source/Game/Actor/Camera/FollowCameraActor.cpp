#include "FollowCameraActor.h"
#include "../../Graphics/Renderer/Renderer.h"
#include "../../Game.h"
#include "../../Input/KeyBoard.h"
#include "../../Input/Mouse.h"
#include "../../Camera/FollowCamera.h"


FollowCameraActor::FollowCameraActor(const std::weak_ptr<class Game>& game, const std::weak_ptr<class Actor>& follower)
	: Actor(game)
	, mFollower(follower)
{
	std::cerr << "Create FollowCameraActor\n";
}

FollowCameraActor::~FollowCameraActor()
{
	std::cerr << "Destory FollowCameraActor\n";
}

void FollowCameraActor::initailize()
{
	Actor::initailize();

	//Create FollowCamera
	mFollowCamera = std::make_shared<FollowCamera>(weak_from_this(), mFollower);
	mFollowCamera->initailize();
}

void FollowCameraActor::updateActor(float deltatime)
{
}

void FollowCameraActor::actorInput()
{
	auto game = getGame().lock();

	float yawSpeed = 0.0f;
	float pitchSpeed = 0.0f;

	//Mouse Rotate
	Vector2 mouseRelativePos = game->getMouse()->getPosition() - game->getMouse()->getOriginPosition();

	const float maxMouseSpeed = 500.0f;

	if (mouseRelativePos.x != 0.0f)
	{
		yawSpeed = mouseRelativePos.x / maxMouseSpeed;
		yawSpeed *= Math::Pi * 12;
	}
	if (mouseRelativePos.y != 0.0f)
	{
		pitchSpeed = mouseRelativePos.y / maxMouseSpeed;
		pitchSpeed *= Math::Pi * 12;
	}
	mFollowCamera->setYawSpeed(yawSpeed);
	mFollowCamera->setPitchSpeed(pitchSpeed);

	bool updateFollower = false;
	
	auto actor = mFollower.lock();
	Vector3 a = Vector3::Zero;
	Vector3 b = actor->getForward();

	if (game->getKeyBoard()->isKeyPressed('w'))
	{
		a += getForward();
		updateFollower = true;
	}
	if (game->getKeyBoard()->isKeyPressed('s'))
	{
		a -= getForward();
		updateFollower = true;
	}
	if (game->getKeyBoard()->isKeyPressed('a'))
	{
		a -= getSide();
		updateFollower = true;
	}
	if (game->getKeyBoard()->isKeyPressed('d'))
	{
		a += getSide();
		updateFollower = true;
	}

	if (updateFollower)
	{
		a.y = b.y = 0.0f;
		a.Normalize();
		b.Normalize();

		float rad = Vector3::Dot(a, b);
		rad = Math::Clamp(rad, -1.0f, 1.0f);
		rad = Math::Acos(rad);

		if (!Math::NearZero(rad))
		{
			if (Vector3::Cross(a, b).y > 0.0f)
				rad *= -1;

			actor->setRotation(Quaternion::Concatenate(actor->getRotation(), Quaternion(actor->getUp(), rad)));
			b = actor->getForward();
		}
	}
}