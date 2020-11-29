#pragma once
#include <string>
#include "../../Component/Component.h"
#include "../../Graphics/Renderer/Renderer.h"

class CubeMapComponent : public Component
{
public:
	CubeMapComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render);
	virtual ~CubeMapComponent() noexcept;

	virtual void initailize() override;

	virtual void draw(std::unique_ptr<class Shader>& shader);
	void setTexture(const std::vector<std::string>& files);

	int getTexWidth() const { return mTexWidth; }
	int getTexHeight() const { return mTexHeight; }

private:
	std::weak_ptr<class Renderer> mRender;
	std::shared_ptr<class Texture> mTexture;
	int mTexWidth;
	int mTexHeight;
	unsigned int mTextureID = 0;
};

class CubeMaps : public std::enable_shared_from_this<CubeMaps>
{
public:
	CubeMaps(const std::weak_ptr<class Renderer>& render);
	~CubeMaps() noexcept;

private:
	
	std::weak_ptr<class Renderer> mRender;
	unsigned int mTextureID = 0;
	unsigned int skyboxVao, skyboxVbo;
public:
	void initailize();
	void makeVao();
	void loadCubemap();
	unsigned int getTextureID() const { return mTextureID; }
	void draw(std::unique_ptr<class Shader>& shader);
};