#include "CubeMapComponent.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Texture/Texture.h"
#include "../Texture/stb_image.h"


CubeMapComponent::CubeMapComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render)
	: Component(owner)
	, mRender(render)
	, mTexWidth(0)
	, mTexHeight(0)
{

}

CubeMapComponent::~CubeMapComponent()
{
	mRender.lock()->removeCubeMapComponent(std::dynamic_pointer_cast<CubeMapComponent>(weak_from_this().lock()));
}

void CubeMapComponent::initailize()
{
	Component::initailize();
	mRender.lock()->addCubeMapComponent(std::dynamic_pointer_cast<CubeMapComponent>(weak_from_this().lock()));
}

void CubeMapComponent::draw(std::unique_ptr<Shader>& shader)
{
	shader->setMatrixUniform("uWorldTransform", mOwner.lock()->getWorldTransform());

	//Texture::setActiveskybox(mTextureID);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeMapComponent::setTexture(const std::vector<std::string>& files)
{
	mTextureID = Texture::loadskybox(files);
	std::cout << mTextureID << std::endl;
}




CubeMaps::CubeMaps(const std::weak_ptr<class Renderer>& render)
	: mRender(render)
	,skyboxVao(0)
	,skyboxVbo(0)
{
	
}

CubeMaps::~CubeMaps()
{

}

void CubeMaps::initailize()
{
	makeVao();
	loadCubemap();
	mRender.lock()->addCubeMap(std::dynamic_pointer_cast<CubeMaps>(weak_from_this().lock()));
}

void CubeMaps::makeVao()
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};


	glGenVertexArrays(1, &skyboxVao);
	glGenBuffers(1, &skyboxVbo);
	glBindVertexArray(skyboxVao);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void CubeMaps::loadCubemap()
{
	std::vector<std::string> faces{
		"Asset/Image/SkyBox/right.jpg",
		"Asset/Image/SkyBox/left.jpg",
		"Asset/Image/SkyBox/top.jpg",
		"Asset/Image/SkyBox/bottom.jpg",
		"Asset/Image/SkyBox/front.jpg",
		"Asset/Image/SkyBox/back.jpg",

	};

	//unsigned  int mTextureID;
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

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


	for (auto a : faces)
	{
		//mName = a.c_str();
		std::cerr << a.c_str() << " load complete\n";
	}


}

void CubeMaps::draw(std::unique_ptr<class Shader>& shader)
{
	glDepthMask(GL_FALSE);
	shader->setActive();
	// ... view, projection 행렬 설정
	glBindVertexArray(skyboxVao);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}