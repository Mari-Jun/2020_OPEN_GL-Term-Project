#include "CubeMapComponent.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Texture/Texture.h"


CubeMapComponent::CubeMapComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render)
	: Component(owner)
	, mRender(render)
	, mTexWidth(0)
	, mTexHeight(0)
{

}

CubeMapComponent::~CubeMapComponent()
{
	mRender.lock()->removeCubeMapComponent(std::dynamic_pointer_cast<CubeMapComponent>(weak_from_this().lock()));
}

void CubeMapComponent::initailize()
{
	Component::initailize();
	mRender.lock()->addCubeMapComponent(std::dynamic_pointer_cast<CubeMapComponent>(weak_from_this().lock()));
}

void CubeMapComponent::draw(std::unique_ptr<Shader>& shader)
{
	if (mTexture)
	{
		shader->setMatrixUniform("uWorldTransform", mOwner.lock()->getWorldTransform());
		Texture::setActiveskybox(mTextureID);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void CubeMapComponent::setTexture(const std::vector<std::string>& files)
{
	Texture::loadskybox(files);
}