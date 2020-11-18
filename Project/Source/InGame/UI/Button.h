#pragma once
#include "../../Game/Actor/Actor.h"
#include "../../Game/Math/Math.h"
#include <string>
#include <memory>
#include <functional>

class Button
{
public:
	Button(std::function<void()> click, const Vector2& pos);
	~Button();

	virtual void initailize();

	bool containMouse(const Vector2& pos) const;
	void click();

private:
	std::function<void()> mClick;
	std::shared_ptr<class Texture> mTexture;
	Vector2 mPosition;
	Vector2 mRange;

public:
	const Vector2& getPosition() const { return mPosition; }
};
