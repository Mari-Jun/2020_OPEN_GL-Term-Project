#include "MeshComponent.h"
#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Texture/Texture.h"


MeshComponent::MeshComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render)
	: Component(owner)
	, mRender(render)
	, mTextureIndex(0)
{

}

MeshComponent::~MeshComponent()
{
	mRender.lock()->removeMeshComponent(std::dynamic_pointer_cast<MeshComponent>(weak_from_this().lock()));
}

void MeshComponent::initailize()
{
	Component::initailize();
	mRender.lock()->addMeshComponent(std::dynamic_pointer_cast<MeshComponent>(weak_from_this().lock()));
}

void MeshComponent::draw(std::unique_ptr<Shader>& shader)
{
	if (mMesh)
	{
		shader->setMatrixUniform("uWorldTransform", mOwner.lock()->getWorldTransform());
		shader->SetVectorUniform("uColor", mColor);

		auto texture = mMesh->getTexture(mTextureIndex);
		if (!texture.expired())
		{
			texture.lock()->setActive();
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

void MeshComponent::setTexture(const std::string& fileName)
{
	if (mMesh)
	{
		mMesh->setTexture(fileName, mRender);
	}
}