#include "Capsule.h"

Capsule::Capsule(const Vector3& start, const Vector3& end, float radius)
	:mSegment(start, end)
	, mRadius(radius)
{
}

Vector3 Capsule::PointOnSegment(float t) const
{
	return mSegment.PointOnSegment(t);
}

bool Capsule::Contains(const Vector3& point) const
{
	// Get minimal dist. sq. between point and line segment
	float distSq = mSegment.MinDistSq(point);
	return distSq <= (mRadius * mRadius);
}