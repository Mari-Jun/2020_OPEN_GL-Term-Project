#pragma once
#include <string>

#include <iostream>
#include <vector>

class Texture
{
public:
	Texture();
	~Texture();

	bool load(const std::string& fileName);
	static unsigned int loadskybox (const std::vector<std::string>& faces);
	void unLoad();

	void setActive();
	static void setActiveskybox(unsigned int);

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