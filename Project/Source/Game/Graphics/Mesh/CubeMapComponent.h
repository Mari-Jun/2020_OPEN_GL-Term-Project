#pragma once
#include <string>
#include "../../Component/Component.h"
#include "../../Graphics/Renderer/Renderer.h"

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