#include "BillBoardComponent.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Texture/Texture.h"


BillBoardComponent::BillBoardComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render)
	: Component(owner)
	, mRender(render)
	, mTexWidth(0)
	, mTexHeight(0)
{

}

BillBoardComponent::~BillBoardComponent()
{
	mRender.lock()->removeBillBoardComponent(std::dynamic_pointer_cast<BillBoardComponent>(weak_from_this().lock()));
}

void BillBoardComponent::initailize()
{
	Component::initailize();
	mRender.lock()->addBillBoardComponent(std::dynamic_pointer_cast<BillBoardComponent>(weak_from_this().lock()));
}

void BillBoardComponent::draw(std::unique_ptr<Shader>& shader)
{
	if (mTexture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		Matrix4 pi = mOwner.lock()->getWorldTransform();

		shader->setMatrixUniform("uWorldTransform", pi);
		shader->SetVectorUniform("uAmbientLight", Vector3(1.0f, 1.0f, 1.0f));
		shader->SetVectorUniform("uColor", Vector3(1.0f, 1.0f, 1.0f));

		mTexture->setActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void BillBoardComponent::setTexture(const std::shared_ptr<class Texture>& texture)
{
	mTexture = texture;
	mTexWidth = texture->getWidth();
	mTexHeight = texture->getHeight();
}