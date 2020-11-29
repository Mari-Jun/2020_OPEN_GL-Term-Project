#include "CubeMapComponent.h"
#include "../Renderer/Renderer.h"
#include "../../Actor/Actor.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Texture/Texture.h"
#include "../Texture/stb_image.h"


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
	//float skyboxVertices[] = {
	//	 positions          
	//	-1.0f,  1.0f, -1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	 1.0f, -1.0f, -1.0f,
	//	 1.0f, -1.0f, -1.0f,
	//	 1.0f,  1.0f, -1.0f,
	//	-1.0f,  1.0f, -1.0f,

	//	-1.0f, -1.0f,  1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f,  1.0f, -1.0f,
	//	-1.0f,  1.0f, -1.0f,
	//	-1.0f,  1.0f,  1.0f,
	//	-1.0f, -1.0f,  1.0f,

	//	 1.0f, -1.0f, -1.0f,
	//	 1.0f, -1.0f,  1.0f,
	//	 1.0f,  1.0f,  1.0f,
	//	 1.0f,  1.0f,  1.0f,
	//	 1.0f,  1.0f, -1.0f,
	//	 1.0f, -1.0f, -1.0f,

	//	-1.0f, -1.0f,  1.0f,
	//	-1.0f,  1.0f,  1.0f,
	//	 1.0f,  1.0f,  1.0f,
	//	 1.0f,  1.0f,  1.0f,
	//	 1.0f, -1.0f,  1.0f,
	//	-1.0f, -1.0f,  1.0f,

	//	-1.0f,  1.0f, -1.0f,
	//	 1.0f,  1.0f, -1.0f,
	//	 1.0f,  1.0f,  1.0f,
	//	 1.0f,  1.0f,  1.0f,
	//	-1.0f,  1.0f,  1.0f,
	//	-1.0f,  1.0f, -1.0f,

	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f,  1.0f,
	//	 1.0f, -1.0f, -1.0f,
	//	 1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f,  1.0f,
	//	 1.0f, -1.0f,  1.0f
	//};

	float skyboxVertices[] = {
		0.5,-0.5,0.5,	//5
		0.5,0.5,-0.5,	//6		567¿À¸¥ÂÊ¸é
		0.5,0.5,0.5,	//7
		0.5,-0.5,-0.5,	//4
		0.5,0.5,-0.5,	//6		465¿À¸¥ÂÊ¸é
		0.5,-0.5,0.5,	//5

		-0.5,-0.5,-0.5,	//0							
		-0.5,-0.5,0.5,	//1							
		-0.5,0.5,-0.5,	//2  012»ï°¢Çü ¿ÞÂÊ¸é
		-0.5,-0.5,0.5,	//1							
		-0.5,0.5,0.5,	//3							
		-0.5,0.5,-0.5,	//2  132»ï°¢Çü ¿ÞÂÊ¸é		  	

		-0.5,0.5,-0.5,	//2  
		-0.5,0.5,0.5,	//3	236 À­¸é
		0.5,0.5,-0.5,	//6
		-0.5,0.5,0.5,	//3
		0.5,0.5,0.5,	//7	376À­¸é
		0.5,0.5,-0.5,	//6

		-0.5,-0.5,-0.5,	//0
		0.5,-0.5,-0.5,	//4	041 ¾Æ·§¸é
		-0.5,-0.5,0.5,	//1
		-0.5,-0.5,0.5,	//1
		0.5,-0.5,-0.5,	//4	145 ¾Æ·§¸é
		0.5,-0.5,0.5,	//5

		-0.5,-0.5,0.5,	//1
		0.5,-0.5,0.5,	//5	153¾Õ¸é
		-0.5,0.5,0.5,	//3
		-0.5,0.5,0.5,	//3
		0.5,-0.5,0.5,	//5	357¾Õ¸é
		0.5,0.5,0.5,	//7



		-0.5,0.5,-0.5,	//2  264 µÞ¸é
		0.5,0.5,-0.5,	//6
		0.5,-0.5,-0.5,	//4
		-0.5,-0.5,-0.5,	//0
		-0.5,0.5,-0.5,	//2  024 µÞ¸é
		0.5,-0.5,-0.5,	//4


	};

	glGenVertexArrays(1, &skyboxVao);
	glBindVertexArray(skyboxVao);

	glGenBuffers(1, &skyboxVbo);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void CubeMaps::loadCubemap()
{
	std::vector<std::string> faces{
		"Asset/Image/SkyBox/sunrise/left.png",
		"Asset/Image/SkyBox/sunrise/right.png",
		"Asset/Image/SkyBox/sunrise/top.png",
		"Asset/Image/SkyBox/sunrise/bottom.png",
		"Asset/Image/SkyBox/sunrise/front.png",
		"Asset/Image/SkyBox/sunrise/back.png",

	};
	

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

	int width, height, nrChannels;

	int format = GL_RGB;



	for (GLuint i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		
		stbi_set_flip_vertically_on_load(true);
		if (data)
		{
			if (nrChannels == 4)
			{
				format = GL_RGBA;
			}
			else if (nrChannels == 3)
			{
				format = GL_RGB;
			}
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
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
	glBindVertexArray(skyboxVao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}