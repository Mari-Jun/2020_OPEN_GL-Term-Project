#include "AlphaComponent.h"
#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Texture/Texture.h"


AlphaComponent::AlphaComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render)
	: Component(owner)
	, mRender(render)
	, mColor(Vector3(1.0f, 1.0f, 1.0f))
	, mAlpha(0.5f)
	, mTextureIndex(0)
{

}

AlphaComponent::~AlphaComponent()
{
	mRender.lock()->removeAlphaComponent(std::dynamic_pointer_cast<AlphaComponent>(weak_from_this().lock()));
}

void AlphaComponent::initailize()
{
	Component::initailize();
	mRender.lock()->addAlphaComponent(std::dynamic_pointer_cast<AlphaComponent>(weak_from_this().lock()));
}

void AlphaComponent::draw(std::unique_ptr<Shader>& shader)
{
	if (mMesh)
	{
		shader->setMatrixUniform("uWorldTransform", mOwner.lock()->getWorldTransform());
		shader->SetVectorUniform("uColor", mColor);
		shader->SetFloatUniform("uAlpha", mAlpha);

		auto texture = mMesh->getTexture(mTextureIndex);
		if (!texture.expired())
		{
			texture.lock()->setActive();
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		mMesh->getVertexArray()->setActive();

		if (mMesh->getVertexArray()->getIndexNum() == 0)
		{
			glDrawArrays(GL_TRIANGLES, 0, mMesh->getVertexArray()->getVertexNum());
		}
		else
		{
			glDrawElements(GL_TRIANGLES, mMesh->getVertexArray()->getIndexNum(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void AlphaComponent::setTexture(const std::string& fileName)
{
	if (mMesh)
	{
		mMesh->setTexture(fileName, mRender);
	}
}