#pragma once
#include "../../Math/Math.h"

struct DirectionalLight
{
	Vector3 direction;
	Vector3 diffuseColor;
	Vector3 specularColor;
	float intensity;
};

DirectionalLight loadDirectionalLight();