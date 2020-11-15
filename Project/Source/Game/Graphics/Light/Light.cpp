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
	mAmbientLight = Vector3(0.2f, 0.2f, 0.2f);

	DirectionalLight dirLight;
	dirLight.direction = Vector3(0.0f, -1.0f, 0.0f);
	dirLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dirLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	dirLight.intensity = 1.0f;

	mDirLight.push_back(dirLight);
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
	//Ambient light
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	//Direction light
	for (const auto& dir : mDirLight)
	{
		shader->SetVectorUniform("uDirLight.direction", dir.direction);
		shader->SetVectorUniform("uDirLight.diffuseColor", dir.diffuseColor * dir.intensity);
		shader->SetVectorUniform("uDirLight.specularColor", dir.specularColor);
	}

	shader->SetFloatUniform("uSpecBrightness", 64.0f);
}

DirectionalLight loadDirectionalLight()
{
	DirectionalLight mDirLight;
	mDirLight.direction = Vector3::Normalize(Vector3(1.0f, 1.0f, -1.0f));
	mDirLight.diffuseColor = Vector3(1.0f, 0.0f, 0.0f);
	mDirLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	mDirLight.intensity = 1.0f;	
	return mDirLight;
}
