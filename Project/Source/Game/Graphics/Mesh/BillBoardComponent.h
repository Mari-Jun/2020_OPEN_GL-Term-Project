#pragma once
#include <string>
#include "../../Component/Component.h"
#include "../../Graphics/Renderer/Renderer.h"

class BillBoardComponent : public Component
{
public:
	BillBoardComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render);
	virtual ~BillBoardComponent() noexcept;

	virtual void initailize() override;

	virtual void draw(std::unique_ptr<class Shader>& shader);
	void setTexture(const std::shared_ptr<class Texture>& texture);

	int getTexWidth() const { return mTexWidth; }
	int getTexHeight() const { return mTexHeight; }

private:
	std::weak_ptr<class Renderer> mRender;
	std::shared_ptr<class Texture> mTexture;
	int mTexWidth;
	int mTexHeight;
};