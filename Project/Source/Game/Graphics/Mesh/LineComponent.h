#pragma once
#include "../../Component/Component.h"

class LineComponent : public Component
{
public:
	LineComponent(const std::weak_ptr<class Actor>& owner, const std::weak_ptr<class Renderer>& render);
	virtual ~LineComponent() noexcept;

	virtual void initailize() override;

	virtual void draw(std::unique_ptr<class Shader>& shader);

	void setMesh(const std::shared_ptr<class Mesh>& mesh) { mMesh = mesh; }
	void setColor(Vector3 color) { mColor = color; }

private:
	std::weak_ptr<class Renderer> mRender;
	std::shared_ptr<class Mesh> mMesh;
	Vector3 mColor;
};
