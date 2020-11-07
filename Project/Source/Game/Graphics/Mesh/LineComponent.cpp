#include "LineComponent.h"
#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"


LineComponent::LineComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render)
	: Component(owner)
	, mRender(render)
{
	std::cerr << "Create LineComponent\n";
}

LineComponent::~LineComponent()
{
	mRender.lock()->removeLineComponent(std::dynamic_pointer_cast<LineComponent>(weak_from_this().lock()));
	std::cerr << "Destory LineComponent\n";
}

void LineComponent::initailize()
{
	Component::initailize();
	mRender.lock()->addLineComponent(std::dynamic_pointer_cast<LineComponent>(weak_from_this().lock()));
}

void LineComponent::draw(std::unique_ptr<Shader>& shader)
{
	if (mMesh)
	{
		shader->setMatrixUniform("uWorldTransform", mOwner.lock()->getWorldTransform());
		shader->SetVectorUniform("uColor", mColor);

		mMesh->getVertexArray()->setActive();

		if (mMesh->getVertexArray()->getIndexNum() == 0)
		{
			glDrawArrays(GL_LINE_STRIP, 0, mMesh->getVertexArray()->getVertexNum());
		}
		else
		{
			glDrawElements(GL_LINE_STRIP, mMesh->getVertexArray()->getIndexNum(), GL_UNSIGNED_INT, nullptr);
		}
	}
}