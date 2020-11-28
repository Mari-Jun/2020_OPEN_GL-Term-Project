#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "../Shader/VertexArray.h"
#include "../../Physics/Coliision/Collision.h"

struct MTL
{
	Vector3 ambientColor;
	Vector3 diffuseColor;
	Vector3 specularColor;
};

class Mesh final
{
public:
	Mesh();
	~Mesh();

	bool load(const std::string& fileName);
	bool load(const std::string& fileName, std::unordered_map<std::string, MTL>& mtl);
	void unLoad();

	const AABB& getBox() const { return mBox; }
	void setBox(const AABB& box) { mBox = box; }

	void resetTexture();
	void setTexture(const std::string& fileName, const std::weak_ptr<class Renderer>& mRender);
	std::weak_ptr<class Texture> getTexture(int index);
	int getTextureSize() const { return static_cast<int>(mTexture.size()); }

	void setVertexArray(const std::shared_ptr<class VertexArray>& va) { mVertexArray = va; }
	const std::shared_ptr<class VertexArray>& getVertexArray() const { return mVertexArray; }

private:
	AABB mBox;
	std::vector<std::weak_ptr<class Texture>> mTexture;
	std::shared_ptr<class VertexArray> mVertexArray;
};

std::shared_ptr<Mesh> createBoxMesh();
std::shared_ptr<Mesh> createCircleMesh();
std::shared_ptr<Mesh> createRectMesh();