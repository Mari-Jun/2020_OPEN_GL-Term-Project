#include <fstream>
#include <sstream>
#include <algorithm>
#include "Mesh.h"
#include "../Renderer/Renderer.h"

Mesh::Mesh()
	: mVertexArray(nullptr)
	, mBox(Vector3::Zero, Vector3::Zero)
{

}

Mesh::~Mesh()
{

}

bool Mesh::load(const std::string& fileName)
{
	//Open Obj file
	std::string objName = fileName + ".obj";
	std::ifstream meshFile(objName);

	if (!meshFile.is_open())
	{
		std::cerr << "Obj file not found : " << objName << '\n';
		return false;
	}
	
	std::unordered_map<std::string, MTL> mtl;
	if (!load(fileName, mtl))
		return false;

	std::vector<Vector3> position;
	std::vector<Vector2> texcoord;
	std::vector<Vector3> normal;
	std::vector<Vector3> color;

	std::vector<unsigned int> pIndex;
	std::vector<unsigned int> tIndex;
	std::vector<unsigned int> nIndex;
	std::vector<std::string> mtlIndex;

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	std::string mtlName;
	Vector3 vec3;
	Vector2 vec2;
	unsigned int tempUInt = 0;

	while (std::getline(meshFile, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "v")
		{
			ss >> vec3.x >> vec3.y >> vec3.z;
			position.push_back(vec3);
		}
		else if (prefix == "vn")
		{
			ss >> vec3.x >> vec3.y >> vec3.z;
			normal.push_back(vec3);
		}
		else if (prefix == "vt")
		{
			ss >> vec2.x >> vec2.y;
			texcoord.push_back(vec2);
		}
		else if (prefix == "usemtl")
		{
			ss >> mtlName;
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> tempUInt)
			{
				if (counter == 0)
				{
					pIndex.push_back(tempUInt - 1);
					mtlIndex.push_back(mtlName);
				}
				else if (counter == 1)
				{
					tIndex.push_back(tempUInt - 1);
				}
				else if (counter == 2)
				{
					nIndex.push_back(tempUInt - 1);
				}

				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}
				if (counter > 2)
					counter = 0;
			}
		}
	}

	std::vector<Vertex> vertex;
	vertex.resize(pIndex.size(), Vertex());

	for (auto index = 0; index < vertex.size(); ++index)
	{
		vertex[index].position = position[pIndex[index]];
		vertex[index].texcoord = texcoord[tIndex[index]];
		vertex[index].normal = normal[nIndex[index]];
		vertex[index].ambientColor = mtl[mtlIndex[index]].ambientColor;
		vertex[index].diffuseColor = mtl[mtlIndex[index]].diffuseColor;
		vertex[index].specularColor = mtl[mtlIndex[index]].specularColor;
	}

	setVertexArray(std::make_shared<VertexArray>(vertex, vertex.size(), pIndex, 0));
	for (const auto& index : vertex)
	{
		mBox.UpdateMinMax(Vector3(index.position.x, index.position.y, index.position.z));
	}

	std::cerr << fileName << " load complete\n";

	return true;
}

bool Mesh::load(const std::string& fileName, std::unordered_map<std::string, MTL>& mtl)
{
	//Open Mtl file
	std::string mtlName = fileName + ".mtl";
	std::ifstream mtlFile(mtlName);

	if (!mtlFile.is_open())
	{
		std::cerr << "Mtl file not found : " << mtlName << '\n';
		return false;
	}

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	std::string name;
	MTL color;
	unsigned int tempUInt = 0;

	while (std::getline(mtlFile, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "newmtl")
		{
			ss >> name;
		}
		else if (prefix == "Ka")
		{
			ss >> color.ambientColor.x >> color.ambientColor.y >> color.ambientColor.z;
		}
		else if (prefix == "Kd")
		{
			ss >> color.diffuseColor.x >> color.diffuseColor.y >> color.diffuseColor.z;
		}
		else if (prefix == "Ks")
		{
			ss >> color.specularColor.x >> color.specularColor.y >> color.specularColor.z;
			mtl.emplace(name, color);
		}
		
	}

	return true;
}

void Mesh::unLoad()
{
	mVertexArray.reset();
}

void Mesh::resetTexture()
{
	mTexture.clear();
}

void Mesh::setTexture(const std::string& fileName, const std::weak_ptr<Renderer>& mRender)
{
	const auto& texture = mRender.lock()->getTexture(fileName);
	auto iter = find_if(mTexture.begin(), mTexture.end(),
		[&texture](const std::weak_ptr<Texture>& tex)
		{return texture == tex.lock(); });
	if (iter == mTexture.end())
	{
		mTexture.emplace_back(texture);
	}
	std::cout << mTexture.size() << std::endl;
}

std::weak_ptr<Texture> Mesh::getTexture(int index)
{
	if (index < mTexture.size())
	{
		return mTexture[index];
	}
	else
	{
		return std::weak_ptr<Texture>();
	}
}

std::shared_ptr<Mesh> createBoxMesh()
{
	std::vector<Vertex> vertex(8);

	vertex[0].position = Vector3(-1.0f, -1.0f, 1.0f);
	vertex[1].position = Vector3(-1.0f, -1.0f, -1.0f);
	vertex[2].position = Vector3(1.0f, -1.0f, -1.0f);
	vertex[3].position = Vector3(1.0f, -1.0f, 1.0f);
	vertex[4].position = Vector3(-1.0f, 1.0f, 1.0f);
	vertex[5].position = Vector3(1.0f, 1.0f, 1.0f);
	vertex[6].position = Vector3(1.0f, 1.0f, -1.0f);
	vertex[7].position = Vector3(-1.0f, 1.0f, -1.0f);

	std::vector<unsigned int> Index = {
		0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4,
		0, 3, 5, 5, 4, 0, 3, 2, 6, 6, 5, 3,
		2, 1, 7, 7, 6, 2, 1, 0, 4, 4, 7, 1
	};

	auto mesh = std::make_shared<Mesh>();
	mesh->setVertexArray(std::make_shared<VertexArray>(vertex, vertex.size(), Index, Index.size()));
	AABB box(Vector3::Zero, Vector3::Zero);
	for (const auto& index : vertex)
	{
		box.UpdateMinMax(Vector3(index.position.x, index.position.y, index.position.z));
	}
	mesh->setBox(box);
	return mesh;
}


std::shared_ptr<Mesh> createCircleMesh()
{

	std::vector<Vertex> vertex(181);

	for (int i = 0; i < 181; i++)
	{
		vertex[i].position = Vector3(cos(Math::ToRadians(i * 2)), sin(Math::ToRadians(i * 2)), 0.0f);
	}

	std::vector<unsigned int> Index = {};

	auto mesh = std::make_shared<Mesh>();
	mesh->setVertexArray(std::make_shared<VertexArray>(vertex, vertex.size(), Index, Index.size()));
	AABB box(Vector3::Zero, Vector3::Zero);
	for (const auto& index : vertex)
	{
		box.UpdateMinMax(Vector3(index.position.x, index.position.y, index.position.z));
	}
	mesh->setBox(box);
	return mesh;
}

std::shared_ptr<Mesh> createRectMesh()
{
	std::vector<Vertex> vertex(4);

	vertex[0].position = Vector3(-1.0f, 0.0f, -1.0f);
	vertex[1].position = Vector3(-1.0f, 0.0f, 1.0f);
	vertex[2].position = Vector3(1.0f, 0.0f, 1.0f);
	vertex[3].position = Vector3(1.0f, 0.0f, -1.0f);

	std::vector<unsigned int> Index = {
		0, 1, 2, 0, 2, 3
	};

	auto mesh = std::make_shared<Mesh>();
	mesh->setVertexArray(std::make_shared<VertexArray>(vertex, vertex.size(), Index, Index.size()));
	AABB box(Vector3::Zero, Vector3::Zero);
	for (const auto& index : vertex)
	{
		box.UpdateMinMax(Vector3(index.position.x, index.position.y, index.position.z));
	}
	mesh->setBox(box);
	return mesh;
}