#pragma once
#include <vector>
#include <memory>
#include "../../Math/Math.h"

struct DirectionalLight
{
	Vector3 direction;
	Vector3 diffuseColor;
	Vector3 specularColor;
	float intensity;
};

class Light
{
public:
	Light(const std::weak_ptr<class Renderer>& render);
	~Light();

	void initailize();

	void update(float deltatime);
	void processInput();

	void setLightShader(Matrix4 view, const std::unique_ptr<class Shader>& shader);

	void setRotation(int index, bool rot) { mIsRot[index] = rot; }
	void setAnimation(bool ani) { mAnimation = ani; }

private:
	std::weak_ptr<class Renderer> mRenderer;
	Vector3 mAmbientLight;
	std::vector<struct DirectionalLight> mDirLight;
	bool mIsRot[3];
	bool mAnimation;
};

DirectionalLight loadDirectionalLight();