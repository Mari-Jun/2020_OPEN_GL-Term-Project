#pragma once
#include "../../Math/Math.h"

struct Plane
{
	Plane(const Vector3& normal, float d);
	// Construct plane from three points
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);
	// Get the signed distance between the point and the plane
	float SignedDist(const Vector3& point) const;

	Vector3 mNormal;
	float mD;
};
