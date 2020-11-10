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

	bool initailize(const Vector2& pos, const Vector2& size, std::string name);
	void shutDown();
	void unLoadData();

	void update(float deltatime);
	void processInput();
	void draw();

	void addLineComponent(const std::weak_ptr<class LineComponent>& component);
	void removeLineComponent(const std::weak_ptr<class LineComponent>& component);

	void addMeshComponent(const std::weak_ptr<class MeshComponent>& component);
	void removeMeshComponent(const std::weak_ptr<class MeshComponent>& component);

	void addAlphaComponent(const std::weak_ptr<class AlphaComponent>& component);
	void removeAlphaComponent(const std::weak_ptr<class AlphaComponent>& component);

	void addSpriteComponent(const std::weak_ptr<class SpriteComponent>& component);
	void removeSpriteComponent(const std::weak_ptr<class SpriteComponent>& component);

private:
	bool loadShader();
	void createSpriteVertex();

	std::unordered_map<std::string, std::shared_ptr<class Texture>> mTexture;
	std::unordered_map<std::string, std::shared_ptr<class Mesh>> mMesh;

	std::vector<std::weak_ptr<class LineComponent>> mLineComponent;
	std::vector<std::weak_ptr<class MeshComponent>> mMeshComponent;
	std::vector<std::weak_ptr<class AlphaComponent>> mAlphaComponent;
	std::vector<std::weak_ptr<class SpriteComponent>> mSpriteComponent;

	std::weak_ptr<class Game> mGame;

	std::unique_ptr<class Shader> mMeshShader;
	std::unique_ptr<class Shader> mSpriteShader;
	std::unique_ptr<class VertexArray> mSpriteVertex;
	
	Matrix4 mView;
	Matrix4 mProjection;

	std::unique_ptr<class Light> mLight;
	std::unique_ptr<class Window> mWindow;

public:
	void setViewMatrix(const Matrix4& view) { mView = view; }
	void setProjectionMatrix(const Matrix4& projection) { mProjection = projection; }

	const std::weak_ptr<class Game>& getGame() const { return mGame; }
	std::shared_ptr<class Texture> getTexture(const std::string& fileName);
	std::shared_ptr<class Mesh> getMesh(const std::string& fileName);

	const std::unique_ptr<class Window>& getWindow() const { return mWindow; }
	
private:
	void drawLineComponent();
	void drawMeshComponent();
};