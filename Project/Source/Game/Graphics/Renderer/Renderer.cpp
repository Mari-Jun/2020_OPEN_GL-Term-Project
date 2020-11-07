#include "../Shader/Shader.h"
#include "../Shader/VertexArray.h"
#include "../Mesh/MeshComponent.h"
#include "../Mesh/LineComponent.h"
#include "../Mesh/Mesh.h"
#include "../Texture/Texture.h"
#include "Renderer.h"
#include "../../Game.h"
#include "../../Input/KeyBoard.h"
#include "../Light/Light.h"

Renderer::Renderer(const std::weak_ptr<class Game>& game)
	: mGame(game)
	, mLight(true)
{

}

Renderer::~Renderer()
{

}

bool Renderer::initailize(const Vector2& pos, const Vector2& size, std::string name)
{
	//Create Window
	mWindow = std::make_unique<Window>(pos, size, name);
	if (mWindow == nullptr || !mWindow->initialize())
	{
		std::cerr << "Failed to Create Window\n";
		return false;
	}

	//Load Shader
	if (!loadShader())
	{
		std::cerr << "Failed to load shader\n";
		return false;
	}

	//Load Light Light
	mAmbientLight = Vector3(0.2f, 0.2f, 0.2f);
	mDirLight.push_back(loadDirectionalLight());
	return true;
}

void Renderer::shutDown()
{
	mMeshShader->unLoad();
	mMeshShader.reset();
	mWindow.reset();
}

void Renderer::unLoadData()
{
	for (auto mesh : mMesh)
	{
		mesh.second->unLoad();
	}
	mMesh.clear();
}

void Renderer::update(float deltatime)
{
	if (mGame.lock()->getLightAni())
	{
		mDirLight[0].direction = Vector3::Transform(mDirLight[0].direction, Quaternion(Vector3::UnitY, Math::ToRadians(-200.0f * deltatime)));
	}
}

void Renderer::processInput()
{
	auto game = mGame.lock();

	if (game->getKeyBoard()->isKeyPressed('l'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (game->getKeyBoard()->isKeyPressed('L'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (game->getKeyBoard()->isKeyPressed('c'))
	{
		static int color = 0;
		color += 1;
		color %= 3;
		if (color == 0)
		{
			mDirLight[0].diffuseColor = Vector3(1.0f, 0.0f, 0.0f);
		}
		else if (color == 1)
		{
			mDirLight[0].diffuseColor = Vector3(0.0f, 1.0f, 0.0f);
		}
		else
		{
			mDirLight[0].diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
		}
	}
	if (game->getKeyBoard()->isKeyPressed('m'))
	{
		mLight = true;
		loadShader();
	}
	if (game->getKeyBoard()->isKeyPressed('M'))
	{
		mLight = false;
		loadShader();
	}
}

void Renderer::draw()
{
	mWindow->clear();

	drawMeshComponent();
	
	mWindow->swapBuffer();
}

void Renderer::drawLineComponent()
{
	mMeshShader->setActive();
	mMeshShader->setMatrixUniform("uViewProj", mView * mProjection);

	for (auto lComp : mLineComponent)
	{
		if (lComp.lock())
		{
			lComp.lock()->draw(mMeshShader);
		}
	}
}

void Renderer::drawMeshComponent()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	//glDisable(GL_BLEND);

	mMeshShader->setActive();
	mMeshShader->setMatrixUniform("uViewProj", mView * mProjection);
	setLightShader();

	for (auto mComp : mMeshComponent)
	{
		if (mComp.lock())
		{
			mComp.lock()->draw(mMeshShader);
		}
	}
}

void Renderer::addLineComponent(const std::weak_ptr<class LineComponent>& component)
{
	mLineComponent.emplace_back(component);
}

void Renderer::removeLineComponent(const std::weak_ptr<class LineComponent>& component)
{
	auto iter = std::find_if(mLineComponent.begin(), mLineComponent.end(),
		[&component](const std::weak_ptr<LineComponent>& comp)
		{return component.lock() == comp.lock(); });

	if (iter != mLineComponent.end())
	{
		mLineComponent.erase(iter);
	}
}

void Renderer::addMeshComponent(const std::weak_ptr<class MeshComponent>& component)
{
	mMeshComponent.emplace_back(component);
}

void Renderer::removeMeshComponent(const std::weak_ptr<class MeshComponent>& component)
{
	auto iter = std::find_if(mMeshComponent.begin(), mMeshComponent.end(),
		[&component](const std::weak_ptr<MeshComponent>& comp)
		{return component.lock() == comp.lock(); });

	if (iter != mMeshComponent.end())
	{
		mMeshComponent.erase(iter);
	}
}

bool Renderer::loadShader()
{
	mMeshShader = std::make_unique<Shader>();
	if (mLight)
	{
		if (!mMeshShader->load("Source/Game/Graphics/Shader/Phong.vert", "Source/Game/Graphics/Shader/Phong.frag"))
		{
			return false;
		}
	}
	else
	{
		if (!mMeshShader->load("Source/Game/Graphics/Shader/Phong.vert", "Source/Game/Graphics/Shader/Phong2.frag"))
		{
			return false;
		}
	}
	mMeshShader->setActive();

	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitZ, Vector3::UnitY);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), getWindow()->getSize().x, getWindow()->getSize().y, 25.0f, 10000.0f);
	mMeshShader->setMatrixUniform("uViewProj", mView * mProjection);

	return true;
}

void Renderer::setLightShader()
{
	Matrix4 view = mView;
	view.Invert();
	mMeshShader->SetVectorUniform("uCameraPos", view.GetTranslation());
	//Ambient light
	mMeshShader->SetVectorUniform("uAmbientLight", mAmbientLight);
	//Direction light
	for (auto dLight : mDirLight)
	{
		mMeshShader->SetVectorUniform("uDirLight.direction", dLight.direction);
		mMeshShader->SetVectorUniform("uDirLight.diffuseColor", dLight.diffuseColor * dLight.intensity);
		mMeshShader->SetVectorUniform("uDirLight.specularColor", dLight.specularColor);
	}
	//Specular light
	mMeshShader->SetFloatUniform("uSpecBrightness", 64.0f);
}

std::weak_ptr<class Texture> Renderer::getTexture(const std::string& fileName)
{
	std::shared_ptr<Texture> texture = nullptr;

	//파일이 이미 로드되어있는지 확인합니다.
	auto iter = mTexture.find(fileName);
	if (iter != mTexture.end())
	{
		texture = iter->second;
	}
	else
	{
		texture = std::make_shared<Texture>();
		if (texture->load(fileName))
		{
			mTexture.emplace(fileName, texture);
		}
		else
		{
			texture.reset();
			texture = nullptr;
		}
	}

	return texture;
}

std::shared_ptr<class Mesh> Renderer::getMesh(const std::string& fileName)
{
	std::shared_ptr<Mesh> mesh = nullptr;

	//파일이 이미 로드되어있는지 확인합니다.
	auto iter = mMesh.find(fileName);
	if (iter != mMesh.end())
	{
		mesh = iter->second;
	}
	else
	{
		mesh = std::make_shared<Mesh>();
		if (mesh->load(fileName))
		{
			mMesh.emplace(fileName, mesh);
		}
		else
		{
			mesh.reset();
			mesh = nullptr;
		}
	}

	return mesh;
}