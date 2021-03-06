//랜더러.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../Window.h"
#include "../../Math/Math.h"

class Renderer : public std::enable_shared_from_this<Renderer>
{
public:
	Renderer(const std::weak_ptr<class Game>& game);
	~Renderer();

	bool initailize(const Vector2& size, std::string name);
	void shutDown();
	void unLoadData();

	void update(float deltatime);
	void processInput();
	void draw();
	void draw2();

	void addLineComponent(const std::weak_ptr<class LineComponent>& component);
	void removeLineComponent(const std::weak_ptr<class LineComponent>& component);

	void addMeshComponent(const std::weak_ptr<class MeshComponent>& component);
	void removeMeshComponent(const std::weak_ptr<class MeshComponent>& component);

	void addAlphaComponent(const std::weak_ptr<class AlphaComponent>& component);
	void removeAlphaComponent(const std::weak_ptr<class AlphaComponent>& component);

	void addSpriteComponent(const std::weak_ptr<class SpriteComponent>& component);
	void removeSpriteComponent(const std::weak_ptr<class SpriteComponent>& component);

	void addBillBoardComponent(const std::weak_ptr<class BillBoardComponent>& component);
	void removeBillBoardComponent(const std::weak_ptr<class BillBoardComponent>& component);

	void addUI(const std::weak_ptr<class UI>& ui);
	void removeUI(const std::weak_ptr<class UI>& ui);

	void addMinimap(const std::weak_ptr<class Minimap>& minimap);
	void removeMinimap(const std::weak_ptr<class Minimap>& minimap);

	void addCubeMap(const std::weak_ptr<class CubeMaps>& cubemaps);
	void removeCubeMap();

private:
	bool loadShader();
	void createSpriteVertex();

	std::unordered_map<std::string, std::shared_ptr<class Texture>> mTexture;
	std::unordered_map<std::string, std::shared_ptr<class Mesh>> mMesh;

	//추후에 unordered_map으로 변환하도록 하자
	std::vector<std::weak_ptr<class LineComponent>> mLineComponent;
	std::vector<std::weak_ptr<class MeshComponent>> mMeshComponent;
	std::vector<std::weak_ptr<class AlphaComponent>> mAlphaComponent;
	std::vector<std::weak_ptr<class SpriteComponent>> mSpriteComponent;
	std::vector<std::weak_ptr<class BillBoardComponent>> mBillBoardComponent;
	std::weak_ptr<class CubeMaps> mCubeMaps;

	std::vector<std::weak_ptr<class UI>> mUserInterfaces;
	std::vector<std::weak_ptr<class Minimap>> mMinimap;


	std::weak_ptr<class Game> mGame;

	std::unique_ptr<class Shader> mMeshShader;
	std::unique_ptr<class Shader> mSpriteShader;
	std::unique_ptr<class Shader> mBillBoardShader;
	std::unique_ptr<class VertexArray> mSpriteVertex;
	std::unique_ptr<class Shader> mCubeMapShader;
	std::unique_ptr<class VertexArray> mCubeMapVertex;

	Matrix4 mView;
	Matrix4 mInvertView;
	Matrix4 mProjection;

	std::shared_ptr<class Light> mLight;
	std::unique_ptr<class Window> mWindow;

public:
	void setViewMatrix(const Matrix4& view) { mView = view; setInvertView(); }
	void setInvertView();
	void setProjectionMatrix(const Matrix4& projection) { mProjection = projection; }
	const Matrix4& getViewMatrix() const { return mView; }
	const Matrix4& getInvertViewMatrix() const { return mInvertView; }

	const std::weak_ptr<class Game>& getGame() const { return mGame; }
	std::shared_ptr<class Texture> getTexture(const std::string& fileName);
	std::shared_ptr<class Mesh> getMesh(const std::string& fileName);

	std::shared_ptr<class Texture> loadTexture(const std::string& fileName);
	std::shared_ptr<class Mesh> loadMesh(const std::string& fileName);

	const std::shared_ptr<class Light>& getLight() const { return mLight; }
	const std::unique_ptr<class Window>& getWindow() const { return mWindow; }

private:
	void drawLineComponent();
	void drawMeshComponent();
	void drawBillBoardComponent();
	void drawAlphaComponent();
	void drawSpriteComponent();
	void drawUserInterface();
	void drawMinimapMarker();
	void drawCubeMap();
	bool writefile(const std::string& fileName);
	bool EnableSwapBuffer = TRUE;

public:
	void setEnableSwapBuffer(bool i) { EnableSwapBuffer = i; }
};