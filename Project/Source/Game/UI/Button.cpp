#include "Button.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Graphics/Mesh/SpriteComponent.h"
#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Shader/Shader.h"

Button::Button(std::function<void()> click, const Vector2& pos)
	: mClick(click)
	, mPosition(pos)
	, mOnButton(false)
{

}

Button::~Button()
{

}

void Button::initailize()
{
	
}

void Button::draw(std::unique_ptr<class Shader>& shader)
{
	Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mRange.x), static_cast<float>(mRange.y), 1.0f);
	Matrix4 world = scaleMat * Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));
	shader->setMatrixUniform("uWorldTransform", world);

	mTexture[mOnButton]->setActive();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

bool Button::containMouse(const Vector2& pos) const
{
	return !(
		pos.x < (mPosition.x - mRange.x / 2.0f) ||
		pos.x >(mPosition.x + mRange.x / 2.0f) ||
		pos.y < (mPosition.y - mRange.y / 2.0f) ||
		pos.y >(mPosition.y + mRange.y / 2.0f)
	);
}

void Button::click()
{
	if (mClick)
	{
		mClick();
	}
}

void Button::setTexture(const std::shared_ptr<class Texture>& textureOff, const std::shared_ptr<class Texture>& textureOn)
{
	mTexture[0] = textureOff;
	mTexture[1] = textureOn;
	mRange.x = static_cast<float>(mTexture[0]->getWidth());
	mRange.y = static_cast<float>(mTexture[0]->getHeight());
}

