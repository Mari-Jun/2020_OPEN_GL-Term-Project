//¹Ì´Ï¸Ê.cpp
#include "Minimap.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Input/Mouse.h"
#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Shader/Shader.h"
#include "../Sound/Sound.h"
#include "../Actor/Actor.h"

std::weak_ptr<class Actor> Minimap::mStandard;

Minimap::Minimap(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, const std::weak_ptr<class Actor>& owner, bool standard = false)
	: mScene(scene)
	, mOwner(owner)
	, mTexWidth(0)
	, mTexHeight(0)
	, mRenderer(render)
	, mBackgroundPos(Vector2::Zero)
	, mMapSize(4000, 4000)
	, mMinimapSize(250, 250)
{
	if (standard)
	{
		mStandard = owner;
	}
}

Minimap::~Minimap()
{
	mTexture.reset();
	mRenderer.lock()->removeMinimap(weak_from_this());
}

void Minimap::initailize()
{
	mRenderer.lock()->addMinimap(weak_from_this());
}

void Minimap::update(float deltatime)
{

}


void Minimap::setTexture(const std::shared_ptr<class Texture>& texture)
{
	mTexture = texture;
	mTexWidth = texture->getWidth();
	mTexHeight = texture->getHeight();
}

void Minimap::draw(std::unique_ptr<Shader>& shader)
{
	if (mTexture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		Matrix4 world = scaleMat * Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));
		shader->setMatrixUniform("uWorldTransform", world);

		mTexture->setActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void Minimap::drawTexture(std::unique_ptr<Shader>& shader, const std::shared_ptr<class Texture>& texture, const Vector2& pos)
{
	if (texture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(texture->getWidth()), static_cast<float>(texture->getHeight()), 1.0f);
		//Matrix4 world = scaleMat * Matrix4::CreateTranslation(Vector3(pos.x, pos.y, 0.0f));
		Matrix4 world = scaleMat * Matrix4::CreateTranslation(Vector3(pos.x, 1.0, pos.y));
		shader->setMatrixUniform("uWorldTransform", world);

		texture->setActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void Minimap::drawTexture(std::unique_ptr<Shader>& shader, const Vector2& pos)
{
	if (mTexture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
		//Matrix4 world = scaleMat * Matrix4::CreateTranslation(Vector3(pos.x, pos.y, 0.0f));
		Matrix4 world = scaleMat * Matrix4::CreateTranslation(Vector3(pos.x, 1.0, pos.y));
		shader->setMatrixUniform("uWorldTransform", world);

		mTexture->setActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}