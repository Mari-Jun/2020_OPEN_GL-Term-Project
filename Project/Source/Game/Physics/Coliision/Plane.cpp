#include "Plane.h"

Plane::Plane(const Vector3& normal, float d)
	:mNormal(normal)
	, mD(d)
{
}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
{
	// Compute vectors from a to b and a to c
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	// Cross product and normalize to get normal
	mNormal = Vector3::Cross(ab, ac);
	mNormal.Normalize();
	// d = -P dot n
	mD = -Vector3::Dot(a, mNormal);
}

float Plane::SignedDist(const Vector3& point) const
{
	return Vector3::Dot(point, mNormal) - mD;
}