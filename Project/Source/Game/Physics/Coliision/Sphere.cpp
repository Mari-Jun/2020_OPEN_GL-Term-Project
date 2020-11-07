#include "Sphere.h"

Sphere::Sphere(const Vector3& center, float radius)
	:mCenter(center)
	, mRadius(radius)
{
}

bool Sphere::Contains(const Vector3& point) const
{
	// Get distance squared between center and point
	float distSq = (mCenter - point).LengthSq();
	return distSq <= (mRadius * mRadius);
}