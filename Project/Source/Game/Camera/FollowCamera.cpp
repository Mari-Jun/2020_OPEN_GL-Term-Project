#include "FollowCamera.h"
#include "../Actor/Actor.h"
#include <iostream>

FollowCamera::FollowCamera(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Actor>& follower)
	: CameraComponent(owner)
	, mFollower(follower)
	//, mCameraForward(follower.lock()->getForward())
	, mHDist(70.0f)
	, mVDist(30.0f)
	, mTargetDist(20.0f)	
	, mPitchSpeed(0.0f)
	, mYawSpeed(0.0f)
	, mMaxPitch(Math::Pi / 3.0f)
	, mPitch(0.0f)
{

}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::initailize()
{
	CameraComponent::initailize();
	SnapToIdeal();
}

void FollowCamera::update(float deltatime)
{
	CameraComponent::update(deltatime);

	auto owner = mOwner.lock();

	Vector3 cameraForward = owner->getForward();

	Quaternion yaw(Vector3::UnitY, mYawSpeed * deltatime);
	owner->setRotation(Quaternion::Concatenate(owner->getRotation(), yaw));
	cameraForward = Vector3::Transform(cameraForward, yaw);

	Vector3 up = Vector3::UnitY;
	Vector3 right = Vector3::Cross(up, cameraForward);

	mPitch += mPitchSpeed * deltatime;
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);

	Quaternion pitch(right, mPitch);
	cameraForward = Vector3::Transform(cameraForward, pitch);
	up = Vector3::Transform(up, pitch);

	std::cout << up.x << ", " << up.y << ", " << up.z << std::endl;

	owner->setPosition(updateCameraPos(cameraForward));

	auto follower = mFollower.lock();
	Vector3 target = follower->getPosition() + cameraForward * mTargetDist;
	Matrix4 view = Matrix4::CreateLookAt(owner->getPosition(), target, up);
	setViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	auto owner = mOwner.lock();

	Vector3 cameraForward = owner->getForward();
	owner->setPosition(updateCameraPos(cameraForward));

	auto follower = mFollower.lock();
	Vector3 target = follower->getPosition() + owner->getForward() * mTargetDist;
	Matrix4 view = Matrix4::CreateLookAt(owner->getPosition(), target, Vector3::UnitY);
	setViewMatrix(view);
}

Vector3 FollowCamera::updateCameraPos(Vector3& cameraForward)
{
	auto follower = mFollower.lock();

	Vector3 cameraPos = follower->getPosition();
	cameraPos -= cameraForward * mHDist;
	cameraPos += Vector3::UnitY * mVDist;
	return cameraPos;
}