#pragma once
#include "../../Math/Math.h"
#include "LineSegment.h"

struct Capsule
{
	Capsule(const Vector3& start, const Vector3& end, float radius);
	// Get point along segment where 0 <= t <= 1
	Vector3 PointOnSegment(float t) const;
	bool Contains(const Vector3& point) const;

	LineSegment mSegment;
	float mRadius;
};