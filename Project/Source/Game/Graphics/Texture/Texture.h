#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool load(const std::string& fileName);
	unsigned int loadskybox(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
	void unLoad();

	void setActive();
	void setActiveskybox();

	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }
	unsigned int getTextureID() const { return mTextureID; }

	const std::string& getName() const { return mName; }

private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
	std::string mName;
};