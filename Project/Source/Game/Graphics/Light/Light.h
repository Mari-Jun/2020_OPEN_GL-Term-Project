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

struct PointLight
{
	Vector3 position;
	Vector3 diffuseColor;
	Vector3 specularColor;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	Vector3 position;
	Vector3 direciton;
	Vector3 diffuseColor;
	Vector3 specularColor;

	float cutOff;
	float outCutOff;

	float constant;
	float linear;
	float quadratic;
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

	void resetAllLight();

	void setAmbientLight(const Vector3& light) { mAmbientLight = light; }
	void addDirectionalLight(const std::shared_ptr<DirectionalLight>& light);
	void addPointLight(const std::shared_ptr<PointLight>& light);
	void addSpotLight(const std::shared_ptr<SpotLight>& light);
	void removePointLight(const std::shared_ptr<PointLight>& light);
	void removeSpotLight(const std::shared_ptr<SpotLight>& light);

private:
	std::weak_ptr<class Renderer> mRenderer;
	Vector3 mAmbientLight;
	std::vector<std::shared_ptr<DirectionalLight>> mDirLight;
	std::vector<std::shared_ptr<PointLight>> mPointLight;
	std::vector<std::shared_ptr<SpotLight>> mSpotLight;
	bool mIsRot[3];
	bool mAnimation;
};

DirectionalLight loadDirectionalLight();
PointLight loadPointLight();
SpotLight loadSpotLight();