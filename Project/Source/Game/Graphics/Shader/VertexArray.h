#pragma once
#include <iostream>
#include <vector>
#include "../../Math/Math.h"

struct Vertex
{
	Vector3 position;
	Vector2 texcoord;
	Vector3 normal;
};

class VertexArray final
{ 
public:
	VertexArray(std::vector<Vertex>& vertex, unsigned int vertexNum,
		std::vector<unsigned int>& index, unsigned int indexNum);
	~VertexArray();

	void setActive();

	unsigned int getVertexNum() const { return mVertexNum; }
	unsigned int getIndexNum() const { return mIndexNum; }

private:
	unsigned int mVertexNum;
	unsigned int mIndexNum;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};