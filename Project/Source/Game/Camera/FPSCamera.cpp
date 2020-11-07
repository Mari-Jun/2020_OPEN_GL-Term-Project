#include "FPSCamera.h"
#include "../Actor/Actor.h"

FPSCamera::FPSCamera(const std::weak_ptr<class Actor>& owner)
	: CameraComponent(owner)
{
	
}

FPSCamera::~FPSCamera()
{

}

void FPSCamera::initailize()
{
	CameraComponent::initailize();
}

void FPSCamera::update(float deltatime)
{
	auto actor = mOwner.lock();

	Vector3 cameraPos = actor->getPosition();
	Vector3 target = actor->getPosition() + actor->getForward() * 100.0f;
	Vector3 up = Vector3::UnitY;

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	
	setViewMatrix(view);
}