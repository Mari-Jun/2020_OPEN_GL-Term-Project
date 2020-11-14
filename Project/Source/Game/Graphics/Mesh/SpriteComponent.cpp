#include "SpriteComponent.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Texture/Texture.h"


SpriteComponent::SpriteComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render, int drawOrder)
	: Component(owner, drawOrder)
	, mRender(render)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{

}

SpriteComponent::~SpriteComponent()
{
	mRender.lock()->removeSpriteComponent(std::dynamic_pointer_cast<SpriteComponent>(weak_from_this().lock()));
}

void SpriteComponent::initailize()
{
	Component::initailize();
	mRender.lock()->addSpriteComponent(std::dynamic_pointer_cast<SpriteComponent>(weak_from_this().lock()));
}

void SpriteComponent::draw(std::unique_ptr<Shader>& shader)
{
	if (mTexture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		Matrix4 world = scaleMat * mOwner.lock()->getWorldTransform();
		shader->setMatrixUniform("uWorldTransform", world);

		mTexture->setActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::setTexture(const std::shared_ptr<class Texture>& texture)
{
	mTexture = texture;
	mTexWidth = texture->getWidth();
	mTexHeight = texture->getHeight();
}