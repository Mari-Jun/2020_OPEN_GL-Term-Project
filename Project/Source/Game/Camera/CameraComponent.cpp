#include "CameraComponent.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Actor/Actor.h"
#include "../Game.h"

CameraComponent::CameraComponent(const std::weak_ptr<class Actor>& owner, int updateOrder)
	: Component(owner, updateOrder)
{
	std::cerr << "Create CameraComponenet\n";
}

CameraComponent::~CameraComponent()
{
	std::cerr << "Destory CameraComponent\n";
}

void CameraComponent::initailize()
{
	Component::initailize();
}

void CameraComponent::update(float deltatime)
{

}

void CameraComponent::setViewMatrix(const Matrix4& view)
{
	auto game = mOwner.lock()->getGame().lock();
	game->getRenderer()->setViewMatrix(view);
}