#include "Button.h"
#include "../../Game/Game.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Graphics/Mesh/SpriteComponent.h"
#include "../../Game/Graphics/Texture/Texture.h"

Button::Button(std::function<void()> click, const Vector2& pos)
	: mClick(click)
	, mPosition(pos)
{

}

Button::~Button()
{

}

void Button::initailize()
{

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