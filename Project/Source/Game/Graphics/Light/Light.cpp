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
	//Set Light
	mAmbientLight = Vector3(0.1f, 0.1f, 0.1f);

	DirectionalLight dirLight = loadDirectionalLight();
	//mDirLight.push_back(dirLight);

	PointLight pLight = loadPointLight();
	mPointLight.push_back(pLight);

	SpotLight sLight = loadSpotLight();
	mSpotLight.push_back(sLight);
}

void Light::update(float deltatime)
{
	if (mAnimation)
	{
		Vector3 dir = mDirLight[0].direction;
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
		mDirLight[0].direction = dir;
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
		shader->SetVectorUniform((name + ".direction").c_str(), mDirLight[index].direction);
		shader->SetVectorUniform((name + ".diffuseColor").c_str(), mDirLight[index].diffuseColor);
		shader->SetVectorUniform((name + ".specularColor").c_str(), mDirLight[index].specularColor);
	}

	//Point Light
	shader->SetIntUniform("uPointSize", mPointLight.size());
	for (auto index = 0; index < mPointLight.size(); index++)
	{
		std::string name = "uPointLight[" + std::to_string(index) + "]";
		shader->SetVectorUniform((name + ".position").c_str(), mPointLight[index].position);
		shader->SetVectorUniform((name + ".diffuseColor").c_str(), mPointLight[index].diffuseColor);
		shader->SetVectorUniform((name + ".specularColor").c_str(), mPointLight[index].specularColor);
		shader->SetFloatUniform((name + ".constant").c_str(), mPointLight[index].constant);
		shader->SetFloatUniform((name + ".linear").c_str(), mPointLight[index].linear);
		shader->SetFloatUniform((name + ".quadratic").c_str(), mPointLight[index].quadratic);
	}

	//Spot Light
	shader->SetIntUniform("uSpotSize", mSpotLight.size());
	for (auto index = 0; index < mSpotLight.size(); index++)
	{
		std::string name = "uSpotLight[" + std::to_string(index) + "]";
		shader->SetVectorUniform((name + ".position").c_str(), mSpotLight[index].position);
		shader->SetVectorUniform((name + ".direction").c_str(), mSpotLight[index].direciton);
		shader->SetVectorUniform((name + ".diffuseColor").c_str(), mSpotLight[index].diffuseColor);
		shader->SetVectorUniform((name + ".specularColor").c_str(), mSpotLight[index].specularColor);
		shader->SetFloatUniform((name + ".constant").c_str(), mSpotLight[index].constant);
		shader->SetFloatUniform((name + ".linear").c_str(), mSpotLight[index].linear);
		shader->SetFloatUniform((name + ".quadratic").c_str(), mSpotLight[index].quadratic);
		shader->SetFloatUniform((name + ".cutOff").c_str(), mSpotLight[index].cutOff);
		shader->SetFloatUniform((name + ".outCutOff").c_str(), mSpotLight[index].outCutOff);
	}

	shader->SetFloatUniform("uSpecBrightness", 64.0f);
}

DirectionalLight loadDirectionalLight()
{
	DirectionalLight dirLight;
	dirLight.direction = Vector3(0.0f, -1.0f, 0.0f);
	dirLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dirLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	return dirLight;
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