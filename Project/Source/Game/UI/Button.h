#pragma once
#include "../Actor/Actor.h"
#include "../Math/Math.h"
#include <string>
#include <memory>
#include <functional>

class Button
{
public:
	Button(std::function<void()> click, const Vector2& pos, const std::shared_ptr<class Texture>& texture);
	~Button();

	virtual void initailize();

	void draw(std::unique_ptr<class Shader>& shader);

	bool containMouse(const Vector2& pos) const;
	void click();

private:
	std::function<void()> mClick;
	Vector2 mPosition;
	std::shared_ptr<class Texture> mTexture;
	Vector2 mRange;

public:
	const Vector2& getPosition() const { return mPosition; }
};
