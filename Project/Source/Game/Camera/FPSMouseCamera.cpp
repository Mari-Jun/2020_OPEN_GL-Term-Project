#include "FPSMouseCamera.h"
#include "../Actor/Actor.h"

FPSMouseCamera::FPSMouseCamera(const std::weak_ptr<class Actor>& owner)
	: CameraComponent(owner)
	, mPitchSpeed(0.0f)
	, mPitchMaxSpeed(Math::Pi / 3.0f)
	, mPitch(0.0f)
{

}

FPSMouseCamera::~FPSMouseCamera()
{

}

void FPSMouseCamera::initailize()
{
	CameraComponent::initailize();
}

void FPSMouseCamera::update(float deltatime)
{
	CameraComponent::update(deltatime);

	auto actor = mOwner.lock();

	Vector3 cameraPos = actor->getPosition();

	mPitch += mPitchSpeed * deltatime;
	mPitch = Math::Clamp(mPitch, -mPitchMaxSpeed, mPitchMaxSpeed);

	Quaternion axis(actor->getSide(), mPitch);
	Vector3 viewForward = Vector3::Transform(actor->getForward(), axis);
	Vector3 target = actor->getPosition() + viewForward * 100.0f;

	Vector3 up = Vector3::Transform(Vector3::UnitY, axis);

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);

	setViewMatrix(view);
}