#pragma once
#include "../../Math/Math.h"

struct OBB
{
	Vector3 mCenter;
	Quaternion mRotation;
	Vector3 mExtents;
};