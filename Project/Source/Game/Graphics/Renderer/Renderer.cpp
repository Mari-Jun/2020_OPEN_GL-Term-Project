#include "../Shader/Shader.h"
#include "../Light/Light.h"
#include "../Shader/VertexArray.h"
#include "../Mesh/MeshComponent.h"
#include "../Mesh/AlphaComponent.h"
#include "../Mesh/LineComponent.h"
#include "../Mesh/SpriteComponent.h"
#include "../Mesh/BillBoardComponent.h"
#include "../Mesh/CubeMapComponent.h"
#include "../Mesh/Mesh.h"
#include "../Texture/Texture.h"
#include "Renderer.h"
#include "../../Game.h"
#include "../../Input/KeyBoard.h"
#include "../../UI/UI.h"

Renderer::Renderer(const std::weak_ptr<class Game>& game)
	: mGame(game)
{

}

Renderer::~Renderer()
{

}

bool Renderer::initailize(const Vector2& size, std::string name)
{
	//Create Window
	mWindow = std::make_unique<Window>(size, name);
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

	createSpriteVertex();
	createCubeMapVertex();

	//Create Z Rot Light
	mLight = std::make_shared<Light>(weak_from_this());
	mLight->setRotation(2, true);
	mLight->initailize();

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
	mLight->update(deltatime);
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

	mLight->processInput();
}

void Renderer::draw()
{
	mWindow->clear();

	drawLineComponent();
	drawMeshComponent();
	drawAlphaComponent();
	drawBillBoardComponent();

	drawSpriteComponent();
	drawUserInterface();
	
	mWindow->swapBuffer();
}


void Renderer::drawLineComponent()
{
	mMeshShader->setActive();
	mMeshShader->setMatrixUniform("uViewProj", mView * mProjection);
	mLight->setLightShader(mView, mMeshShader);

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
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glDisable(GL_BLEND);

	mMeshShader->setActive();
	mMeshShader->setMatrixUniform("uViewProj", mView * mProjection);
	mLight->setLightShader(mView, mMeshShader);

	for (const auto& mComp : mMeshComponent)
	{
		mComp.lock()->draw(mMeshShader);
	}
}

void Renderer::drawBillBoardComponent()
{
	mBillBoardShader->setActive();
	mBillBoardShader->setMatrixUniform("uViewProj", mView * mProjection);
	mLight->setLightShader(mView, mBillBoardShader);
	mSpriteVertex->setActive();
	for (const auto& bComp : mBillBoardComponent)
	{
		bComp.lock()->draw(mBillBoardShader);
	}
}

void Renderer::drawAlphaComponent()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	for (const auto& aComp : mAlphaComponent)
	{
		aComp.lock()->draw(mMeshShader);
	}
}

void Renderer::drawSpriteComponent()
{
	glDisable(GL_DEPTH_TEST);

	mSpriteShader->setActive();
	mSpriteVertex->setActive();

	for (const auto& sComp : mSpriteComponent)
	{
		sComp.lock()->draw(mSpriteShader);
	}
}

void Renderer::drawUserInterface()
{
	for (const auto& ui : mUserInterfaces)
	{
		ui.lock()->draw(mSpriteShader);
	}
}

void Renderer::drawCubeMapComponent()
{
	glDepthMask(GL_FALSE);
	mCubeMapShader->setActive();
	mCubeMapVertex->setActive();
	for (const auto& cComp : mCubeMapComponent)
	{
		cComp.lock()->draw(mCubeMapShader);
	}
	glDepthMask(GL_TRUE);
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

void Renderer::addAlphaComponent(const std::weak_ptr<class AlphaComponent>& component)
{
	mAlphaComponent.emplace_back(component);
}

void Renderer::removeAlphaComponent(const std::weak_ptr<class AlphaComponent>& component)
{
	auto iter = std::find_if(mAlphaComponent.begin(), mAlphaComponent.end(),
		[&component](const std::weak_ptr<AlphaComponent>& comp)
		{return component.lock() == comp.lock(); });

	if (iter != mAlphaComponent.end())
	{
		mAlphaComponent.erase(iter);
	}
}

void Renderer::addSpriteComponent(const std::weak_ptr<class SpriteComponent>& component)
{
	int order = component.lock()->getUpdateOrder();
	auto iter = mSpriteComponent.begin();
	for (; iter != mSpriteComponent.end(); ++iter)
	{
		if (order < (*iter).lock()->getUpdateOrder())
		{
			break;
		}
	}
	mSpriteComponent.insert(iter, component);	
}

void Renderer::removeSpriteComponent(const std::weak_ptr<class SpriteComponent>& component)
{
	auto iter = std::find_if(mSpriteComponent.begin(), mSpriteComponent.end(),
		[&component](const std::weak_ptr<SpriteComponent>& comp)
		{return component.lock() == comp.lock(); });

	if (iter != mSpriteComponent.end())
	{
		mSpriteComponent.erase(iter);
	}
}

void Renderer::addBillBoardComponent(const std::weak_ptr<class BillBoardComponent>& component)
{
	mBillBoardComponent.emplace_back(component);
}

void Renderer::removeBillBoardComponent(const std::weak_ptr<class BillBoardComponent>& component)
{
	auto iter = std::find_if(mBillBoardComponent.begin(), mBillBoardComponent.end(),
		[&component](const std::weak_ptr<BillBoardComponent>& comp)
		{return component.lock() == comp.lock(); });

	if (iter != mBillBoardComponent.end())
	{
		mBillBoardComponent.erase(iter);
	}
}

void Renderer::addUI(const std::weak_ptr<class UI>& ui)
{
	mUserInterfaces.emplace_back(ui);
}

void Renderer::removeUI(const std::weak_ptr<class UI>& ui)
{
	auto iter = std::find_if(mUserInterfaces.begin(), mUserInterfaces.end(),
		[&ui](const std::weak_ptr<UI>& u)
		{return ui.lock() == u.lock(); });

	if (iter != mUserInterfaces.end())
	{
		mUserInterfaces.erase(iter);
	}
}
void Renderer::addCubeMapComponent(const std::weak_ptr<class CubeMapComponent>& component)
{
	mCubeMapComponent.emplace_back(component);
}
void Renderer::removeCubeMapComponent(const std::weak_ptr<class CubeMapComponent>& component)
{
	auto iter = std::find_if(mCubeMapComponent.begin(), mCubeMapComponent.end(),
		[&component](const std::weak_ptr<CubeMapComponent>& comp)
	{return component.lock() == comp.lock(); });

	if (iter != mCubeMapComponent.end())
	{
		mCubeMapComponent.erase(iter);
	}
}

bool Renderer::loadShader()
{
	mSpriteShader = std::make_unique<Shader>();
	if (!mSpriteShader->load("Source/Game/Graphics/Shader/Sprite.vert", "Source/Game/Graphics/Shader/Sprite.frag"))
	{
		return false;
	}
	mSpriteShader->setActive();

	Matrix4 viewSprite = Matrix4::CreateSimpleViewProj(getWindow()->getSize().x, getWindow()->getSize().y);
	mSpriteShader->setMatrixUniform("uViewProj", viewSprite);


	mMeshShader = std::make_unique<Shader>();
	if (!mMeshShader->load("Source/Game/Graphics/Shader/Phong.vert", "Source/Game/Graphics/Shader/Phong.frag"))
	{
		return false;
	}
	mMeshShader->setActive();

	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitZ, Vector3::UnitY);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), getWindow()->getSize().x, getWindow()->getSize().y, 25.0f, 1000.0f);
	mMeshShader->setMatrixUniform("uViewProj", mView * mProjection);

	mBillBoardShader = std::make_unique<Shader>();
	if (!mBillBoardShader->load("Source/Game/Graphics/Shader/Board.vert", "Source/Game/Graphics/Shader/Phong.frag"))
	{
		return false;
	}
	mBillBoardShader->setActive();
	mBillBoardShader->setMatrixUniform("uViewProj", mView * mProjection);

	mCubeMapShader = std::make_unique<Shader>();
	if (!mCubeMapShader->load("Source/Game/Graphics/Shader/cubemap.vert", "Source/Game/Graphics/Shader/cubemap.frag"))
	{
		return false;
	}
	mCubeMapShader->setActive();
	mCubeMapShader->setMatrixUniform("uViewProj", mView * mProjection);

	return true;
}

void Renderer::createSpriteVertex()
{
	std::vector<Vertex> vertex(4);

	vertex[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertex[1].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertex[2].position = Vector3(0.5f, 0.5f, 0.0f);
	vertex[3].position = Vector3(0.5f, -0.5f, 0.0f);
	vertex[0].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertex[1].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertex[2].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertex[3].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertex[0].texcoord = Vector2(0.0f, 0.0f);
	vertex[1].texcoord = Vector2(0.0f, 1.0f);
	vertex[2].texcoord = Vector2(1.0f, 1.0f);
	vertex[3].texcoord = Vector2(1.0f, 0.0f);

	std::vector<unsigned int> index = {
		0, 1, 2, 0, 2, 3
	};

	mSpriteVertex = std::make_unique<VertexArray>(vertex, vertex.size(), index, index.size());
}

void Renderer::createCubeMapVertex()
{
	std::vector<Vertex> vertex(36);
	vertex[0].position = Vector3(-1.0f, 1.0f, -1.0f);
	vertex[1].position = Vector3(-1.0f, -1.0f, -1.0f);
	vertex[2].position = Vector3(1.0f, -1.0f, -1.0f);
	vertex[3].position = Vector3(1.0f, -1.0f, -1.0f);
	vertex[4].position = Vector3(1.0f, 1.0f, -1.0f);
	vertex[5].position = Vector3(-1.0f, 1.0f, -1.0f);
	vertex[6].position = Vector3(-1.0f, -1.0f, 1.0f);
	vertex[7].position = Vector3(-1.0f, -1.0f, -1.0f);
	vertex[8].position = Vector3(-1.0f, 1.0f, -1.0f);
	vertex[9].position = Vector3(-1.0f, 1.0f, -1.0f);
	vertex[10].position = Vector3(-1.0f, 1.0f, 1.0f);
	vertex[11].position = Vector3(-1.0f, -1.0f, 1.0f);
	vertex[12].position = Vector3(1.0f, -1.0f, -1.0f);
	vertex[13].position = Vector3(1.0f, -1.0f, 1.0f);
	vertex[14].position = Vector3(1.0f, 1.0f, 1.0f);
	vertex[15].position = Vector3(1.0f, 1.0f, 1.0f);
	vertex[16].position = Vector3(1.0f, 1.0f, -1.0f);
	vertex[17].position = Vector3(1.0f, -1.0f, -1.0f);
	vertex[18].position = Vector3(-1.0f, -1.0f, 1.0f);
	vertex[19].position = Vector3(-1.0f, 1.0f, 1.0f);
	vertex[20].position = Vector3(1.0f, 1.0f, 1.0f);
	vertex[21].position = Vector3(1.0f, 1.0f, 1.0f);
	vertex[22].position = Vector3(1.0f, -1.0f, 1.0f);
	vertex[23].position = Vector3(-1.0f, -1.0f, 1.0f);
	vertex[24].position = Vector3(-1.0f, 1.0f, -1.0f);
	vertex[25].position = Vector3(1.0f, 1.0f, -1.0f);
	vertex[26].position = Vector3(1.0f, 1.0f, 1.0f);
	vertex[27].position = Vector3(1.0f, 1.0f, 1.0f);
	vertex[28].position = Vector3(-1.0f, 1.0f, 1.0f);
	vertex[29].position = Vector3(-1.0f, 1.0f, -1.0f);
	vertex[30].position = Vector3(-1.0f, -1.0f, -1.0f);
	vertex[31].position = Vector3(-1.0f, -1.0f, 1.0f);
	vertex[32].position = Vector3(1.0f, -1.0f, -1.0f);
	vertex[33].position = Vector3(1.0f, -1.0f, -1.0f);
	vertex[34].position = Vector3(-1.0f, -1.0f, 1.0f);
	vertex[35].position = Vector3(1.0f, -1.0f, 1.0f);
	std::vector<unsigned int> index;
	mCubeMapVertex = std::make_unique<VertexArray>(vertex, vertex.size(), index, index.size());
}

void Renderer::setInvertView()
{
	mInvertView = mView;
	mInvertView.Invert();
	mInvertView.mat[3][0] = mInvertView.mat[3][1] = mInvertView.mat[3][2] = 0.0f;
}

std::shared_ptr<class Texture> Renderer::getTexture(const std::string& fileName)
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