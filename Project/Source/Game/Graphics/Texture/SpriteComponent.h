#pragma once
#include <string>
#include "../../Component/Component.h"
#include "../../Graphics/Renderer/Renderer.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render, int drawOrder = 500);
	virtual ~SpriteComponent() noexcept;

	virtual void initailize() override;

	virtual void draw(std::unique_ptr<class Shader>& shader);
	void setTexture(const std::shared_ptr<class Texture>& texture);

	int getDrawOrder() const { return mDrawOrder; }
	int getTexWidth() const { return mTexWidth; }
	int getTexHeight() const { return mTexHeight; }

private:
	std::weak_ptr<class Renderer> mRender;
	std::shared_ptr<class Texture> mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
