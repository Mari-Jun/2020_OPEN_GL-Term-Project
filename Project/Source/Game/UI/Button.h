#pragma once
#include "../Actor/Actor.h"
#include "../Math/Math.h"
#include <string>
#include <memory>
#include <functional>

class Button
{
public:
	Button(std::function<void()> click, const Vector2& pos);
	~Button();

	virtual void initailize();

	void draw(std::unique_ptr<class Shader>& shader);

	bool containMouse(const Vector2& pos) const;
	void click();

private:
	std::function<void()> mClick;
	Vector2 mPosition;
	std::shared_ptr<class Texture> mTexture[2];
	Vector2 mRange;
	bool mOnButton;

public:
	const Vector2& getPosition() const { return mPosition; }
	void setTexture(const std::shared_ptr<class Texture>& textureOff, const std::shared_ptr<class Texture>& textureOn);
	bool getOnButton() const { return mOnButton; }
	void setOnButton(bool on) { mOnButton = on; }
};
