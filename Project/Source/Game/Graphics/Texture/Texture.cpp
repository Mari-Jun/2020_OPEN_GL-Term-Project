#define STB_IMAGE_IMPLEMENTATION

#include <gl/glew.h>
#include "Texture.h"
#include "stb_image.h"
#include <iostream>
#include <vector>

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{

}

Texture::~Texture()
{

}

bool Texture::load(const std::string& fileName)
{
	int channel = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(fileName.c_str(), &mWidth, &mHeight, &channel, 0);

	if (image == nullptr)
	{
		std::cerr << "Error : Failed to load image " << fileName << '\n';
		return false;
	}

	int format = GL_RGB;
	if (channel == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);

	//밈맵 설정
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (GLEW_EXT_texture_filter_anisotropic)
	{
		//이방성 최대값을 얻음
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}
	
	mName = fileName;

	std::cerr << fileName << " load complete\n";

	return true;
}

unsigned int Texture::loadskybox
(
	const std::string& top,
	const std::string& bottom,
	const std::string& left,
	const std::string& right,
	const std::string& front,
	const std::string& back 
)
{
	std::vector<std::string> faces;
	faces.push_back(right);
	faces.push_back(left);
	faces.push_back(top);
	faces.push_back(bottom);
	faces.push_back(back);
	faces.push_back(front);

	unsigned  int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	
	for (GLuint i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}


	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;

}


void Texture::unLoad()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::setActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}