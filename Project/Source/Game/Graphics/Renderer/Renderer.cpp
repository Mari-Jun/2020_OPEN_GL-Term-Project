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
#include "../../Minimap/Minimap.h"
#include <fstream>
#include <sstream>

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
	drawCubeMap();
	drawLineComponent();
	drawMeshComponent();
	drawAlphaComponent();
	drawBillBoardComponent();


	drawSpriteComponent();
	drawUserInterface();
	if (EnableSwapBuffer == TRUE)
		mWindow->swapBuffer();
}

void Renderer::draw2()
{
	//draw multi_Viewport option draw
	// 레이어를 겹쳐서 그려야 할 경우, 그리고 원래 draw말고 다르게 그려야 할 경우
	// 여기에 그려줄것만 따로 빼서 그리세요
	// 겹쳐서 그리기는 함수기때문에 mwindow->clear 는 없습니다.
	// 그리는 부분

	drawMeshComponent();
	drawAlphaComponent();

	drawMinimapMarker();
	mWindow->swapBuffer();
	//--------------
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

void Renderer::drawMinimapMarker()
{
	glDisable(GL_DEPTH_TEST);

	mSpriteShader->setActive();
	mSpriteVertex->setActive();

	for (const auto& minimap : mMinimap)
	{
		minimap.lock()->draw(mSpriteShader);
	}


}

void Renderer::drawCubeMap()
{
	glFrontFace(GL_CCW);
	//glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	auto view = mView;
	view.mat[3][0] = view.mat[3][1] = view.mat[3][2] = 0.0f;


	auto tmp = mView;
	tmp.mat[0][1] = view.mat[1][0];
	tmp.mat[0][2] = view.mat[2][0];
	tmp.mat[0][3] = view.mat[3][0];

	tmp.mat[1][0] = view.mat[0][1];
	tmp.mat[1][2] = view.mat[2][1];
	tmp.mat[1][3] = view.mat[3][1];

	tmp.mat[2][0] = view.mat[0][2] * -1;
	tmp.mat[2][1] = view.mat[1][2] * -1;
	tmp.mat[2][2] = view.mat[2][2] * -1;
	tmp.mat[2][3] = view.mat[3][2] * -1;

	tmp.mat[3][0] = view.mat[0][3];
	tmp.mat[3][1] = view.mat[1][3];
	tmp.mat[3][2] = view.mat[2][3];


	mCubeMapShader->setActive();
	mCubeMapShader->SetIntUniform("skybox", 0);

	mCubeMapShader->setMatrixUniform("view", tmp);
	mCubeMapShader->setMatrixUniform("projection", mProjection);

	if (!mCubeMaps.expired())
	{
		mCubeMaps.lock()->draw(mCubeMapShader);
	}

	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);
	//glEnable(GL_DEPTH_TEST);
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

void Renderer::addMinimap(const std::weak_ptr<class Minimap>& minimap)
{
	mMinimap.emplace_back(minimap);
}

void Renderer::removeMinimap(const std::weak_ptr<class Minimap>& minimap)
{
	auto iter = std::find_if(mMinimap.begin(), mMinimap.end(),
		[&minimap](const std::weak_ptr<Minimap>& m)
	{return minimap.lock() == m.lock(); });

	if (iter != mMinimap.end())
	{
		mMinimap.erase(iter);
	}
}

void Renderer::addCubeMap(const std::weak_ptr<class CubeMaps>& cubemaps)
{
	mCubeMaps = cubemaps;
}

void Renderer::removeCubeMap()
{
	mCubeMaps.reset();
}


bool Renderer::loadShader()
{
	mSpriteShader = std::make_unique<Shader>();
	if (!mSpriteShader->load("Asset/Shader/Sprite.vert", "Asset/Shader/Sprite.frag"))
	{
		return false;
	}
	mSpriteShader->setActive();

	Matrix4 viewSprite = Matrix4::CreateSimpleViewProj(getWindow()->getSize().x, getWindow()->getSize().y);
	mSpriteShader->setMatrixUniform("uViewProj", viewSprite);


	mMeshShader = std::make_unique<Shader>();
	if (!mMeshShader->load("Asset/Shader/Phong.vert", "Asset/Shader/Phong.frag"))
	{
		return false;
	}
	mMeshShader->setActive();

	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitZ, Vector3::UnitY);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), getWindow()->getSize().x, getWindow()->getSize().y, 25.0f, 1000.0f);
	mMeshShader->setMatrixUniform("uViewProj", mView * mProjection);

	mBillBoardShader = std::make_unique<Shader>();
	if (!mBillBoardShader->load("Asset/Shader/Board.vert", "Asset/Shader/Phong.frag"))
	{
		return false;
	}
	mBillBoardShader->setActive();
	mBillBoardShader->setMatrixUniform("uViewProj", mView * mProjection);

	auto proj = Matrix4::CreateOrtho(getWindow()->getSize().x, getWindow()->getSize().y, 25.0f, 1000.0f);
	mCubeMapShader = std::make_unique<Shader>();
	if (!mCubeMapShader->load("Asset/Shader/cubemap.vert", "Asset/Shader/cubemap.frag"))
	{
		return false;
	}
	mCubeMapShader->setActive();
	mCubeMapShader->setMatrixUniform("uViewProj", mView * proj);

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
		writefile(fileName);
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
		writefile(fileName);
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

std::shared_ptr<class Texture> Renderer::loadTexture(const std::string& fileName)
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
std::shared_ptr<class Mesh> Renderer::loadMesh(const std::string& fileName)
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



bool Renderer::writefile(const std::string& obj)
{
	std::string fileName = "Asset/Image/imagefile.txt";

	std::ofstream objFile(fileName, std::ios::app);

	if (!objFile.is_open())
	{
		std::cerr << "file not found : " << fileName << '\n';
		return false;
	}

	objFile << obj << std::endl;


	std::cerr << obj << " write complete\n";

	return true;
}