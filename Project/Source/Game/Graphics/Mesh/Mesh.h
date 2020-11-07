#pragma once
#include <iostream>
#include <memory>
#include "../Shader/VertexArray.h"
#include "../../Physics/Coliision/Collision.h"

class Mesh final
{
public:
	Mesh();
	~Mesh();

	bool load(const std::string& fileName);
	void unLoad();

	const AABB& getBox() const { return mBox; }
	void setBox(const AABB& box) { mBox = box; }

	void setTexture(const std::string& fileName, std::weak_ptr<class Renderer>& mRender);
	std::weak_ptr<class Texture> getTexture(int index);

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