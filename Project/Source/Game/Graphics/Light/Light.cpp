#include "Light.h"

DirectionalLight loadDirectionalLight()
{
	DirectionalLight mDirLight;
	mDirLight.direction = Vector3::Normalize(Vector3(1.0f, 1.0f, -1.0f));
	mDirLight.diffuseColor = Vector3(1.0f, 0.0f, 0.0f);
	mDirLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	mDirLight.intensity = 1.0f;	
	return mDirLight;
}
