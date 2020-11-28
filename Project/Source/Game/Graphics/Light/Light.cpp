#include "Light.h"
#include "../Renderer/Renderer.h"
#include "../../Game.h"
#include "../Shader/Shader.h"
#include "../../Input/KeyBoard.h"

Light::Light(const std::weak_ptr<class Renderer>& render)
	: mRenderer(render)	
	, mIsRot{ false, false, false }
	, mAnimation(false)
{

}

Light::~Light()
{

}

void Light::initailize()
{

}

void Light::update(float deltatime)
{
	if (mAnimation)
	{
		Vector3 dir = mDirLight[0]->direction;
		if (mIsRot[0])
		{
			dir = Vector3::Transform(dir, Quaternion(Vector3::UnitX, Math::ToRadians(-1)));
		}
		if (mIsRot[1])
		{
			dir = Vector3::Transform(dir, Quaternion(Vector3::UnitY, Math::ToRadians(-1)));
		}
		if (mIsRot[2])
		{
			dir = Vector3::Transform(dir, Quaternion(Vector3::UnitZ, Math::ToRadians(-0.5f)));
		}
		mDirLight[0]->direction = dir;
	}
}

void Light::processInput()
{
	auto game = mRenderer.lock()->getGame();
	
	/*if (game.lock()->getKeyBoard()->isKeyPressed('r'))
	{
		mAnimation = true;
	}
	if (game.lock()->getKeyBoard()->isKeyPressed('R'))
	{
		mAnimation = false;
	}*/
}

void Light::setLightShader(Matrix4 view, const std::unique_ptr<class Shader>& shader)
{
	view.Invert();
	shader->SetVectorUniform("uCameraPos", view.GetTranslation());
	
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);

	//Direction light
	shader->SetIntUniform("uDirSize", mDirLight.size());
	for (auto index = 0; index < mDirLight.size(); index++)
	{	
		std::string name = "uDirLight[" + std::to_string(index) + "]";
		shader->SetVectorUniform((name + ".direction").c_str(), mDirLight[index]->direction);
		shader->SetVectorUniform((name + ".diffuseColor").c_str(), mDirLight[index]->diffuseColor * mDirLight[index]->intensity);
		shader->SetVectorUniform((name + ".specularColor").c_str(), mDirLight[index]->specularColor);
	}

	//Point Light
	shader->SetIntUniform("uPointSize", mPointLight.size());
	for (auto index = 0; index < mPointLight.size(); index++)
	{
		auto light = mPointLight[index].lock();
		std::string name = "uPointLight[" + std::to_string(index) + "]";
		shader->SetVectorUniform((name + ".position").c_str(), light->position);
		shader->SetVectorUniform((name + ".diffuseColor").c_str(), light->diffuseColor);
		shader->SetVectorUniform((name + ".specularColor").c_str(), light->specularColor);
		shader->SetFloatUniform((name + ".constant").c_str(), light->constant);
		shader->SetFloatUniform((name + ".linear").c_str(), light->linear);
		shader->SetFloatUniform((name + ".quadratic").c_str(), light->quadratic);
	}

	//Spot Light
	shader->SetIntUniform("uSpotSize", mSpotLight.size());
	for (auto index = 0; index < mSpotLight.size(); index++)
	{
		auto light = mSpotLight[index].lock();
		std::string name = "uSpotLight[" + std::to_string(index) + "]";
		shader->SetVectorUniform((name + ".position").c_str(), light->position);
		shader->SetVectorUniform((name + ".direction").c_str(), light->direciton);
		shader->SetVectorUniform((name + ".diffuseColor").c_str(), light->diffuseColor);
		shader->SetVectorUniform((name + ".specularColor").c_str(), light->specularColor);
		shader->SetFloatUniform((name + ".constant").c_str(), light->constant);
		shader->SetFloatUniform((name + ".linear").c_str(), light->linear);
		shader->SetFloatUniform((name + ".quadratic").c_str(), light->quadratic);
		shader->SetFloatUniform((name + ".cutOff").c_str(), light->cutOff);
		shader->SetFloatUniform((name + ".outCutOff").c_str(), light->outCutOff);
	}

	shader->SetFloatUniform("uSpecBrightness", 64.0f);
}

void Light::resetAllLight()
{
	mDirLight.clear();
	mPointLight.clear();
	mSpotLight.clear();
}

void Light::addDirectionalLight(const std::shared_ptr<DirectionalLight>& light)
{
	mDirLight.emplace_back(light);
}

void Light::addPointLight(const std::shared_ptr<PointLight>& light)
{
	mPointLight.emplace_back(light);
}

void Light::addSpotLight(const std::shared_ptr<SpotLight>& light)
{
	mSpotLight.emplace_back(light);
}

void Light::removePointLight(const std::weak_ptr<PointLight>& light)
{
	auto iter = std::find_if(mPointLight.begin(), mPointLight.end(),
		[&light](const std::weak_ptr<PointLight>& lgt)
		{return light.lock() == lgt.lock(); });

	if (iter != mPointLight.end())
	{
		mPointLight.erase(iter);
	}
}
void Light::removeSpotLight(const std::weak_ptr<SpotLight>& light)
{
	auto iter = std::find_if(mSpotLight.begin(), mSpotLight.end(),
		[&light](const std::weak_ptr<SpotLight>& lgt)
		{return light.lock() == lgt.lock(); });

	if (iter != mSpotLight.end())
	{
		mSpotLight.erase(iter);
	}
}

std::shared_ptr<DirectionalLight> loadDirectionalLight()
{
	DirectionalLight dirLight;
	dirLight.direction = Vector3(0.0f, -1.0f, 0.0f);
	dirLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dirLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	dirLight.intensity = 1.0f;
	return std::make_shared<DirectionalLight>(dirLight);
}

PointLight loadPointLight()
{
	PointLight pLight;
	pLight.position = Vector3(0.0f, 110.0f, 0.0f);
	pLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	pLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	pLight.constant = 1.0f;
	pLight.linear = 0.014f;
	pLight.quadratic = 0.0007f;
	return pLight;
}

SpotLight loadSpotLight()
{
	SpotLight pLight;
	pLight.position = Vector3(0.0f, 110.0f, -400.0f);
	pLight.direciton = Vector3::UnitZ;
	pLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	pLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	pLight.constant = 1.0f;
	pLight.linear = 0.014f;
	pLight.quadratic = 0.0007f;
	pLight.cutOff = Math::ToRadians(12.5f);
	pLight.outCutOff = Math::ToRadians(15.0f);
	return pLight;
}