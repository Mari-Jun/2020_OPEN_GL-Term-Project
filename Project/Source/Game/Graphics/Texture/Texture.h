#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool load(const std::string& fileName);
	void unLoad();

	void CreateForRendering(int width, int height, unsigned int format);

	void setActive();

	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }
	unsigned int getTextureID() const { return mTextureID; }

private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};