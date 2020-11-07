#pragma once
#include <string>
#include "../../Component/Component.h"
#include "../../Graphics/Renderer/Renderer.h"

class MeshComponent : public Component
{
public:
	MeshComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render);
	virtual ~MeshComponent() noexcept;

	virtual void initailize() override;

	virtual void draw(std::unique_ptr<class Shader>& shader);

	void setMesh(const std::shared_ptr<class Mesh>& mesh) { mMesh = mesh; }
	void setColor(Vector3 color) { mColor = color; }

	void setTextureIndex(int index) { mTextureIndex = index; }

	void setTexture(const std::string& fileName);

private:
	std::weak_ptr<class Renderer> mRender;
	std::shared_ptr<class Mesh> mMesh;
	Vector3 mColor;
	int mTextureIndex;
};
