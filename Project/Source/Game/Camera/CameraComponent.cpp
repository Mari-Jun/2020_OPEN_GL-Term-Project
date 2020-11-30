#include "CameraComponent.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Actor/Actor.h"
#include "../Sound/Sound.h"
#include "../Game.h"

CameraComponent::CameraComponent(const std::weak_ptr<class Actor>& owner, int updateOrder)
	: Component(owner, updateOrder)
{

}

CameraComponent::~CameraComponent()
{

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
	game->getSound()->setListener(mOwner.lock()->getPosition());
}