#pragma once
#include "../../Math/Math.h"

struct LineSegment
{
	LineSegment(const Vector3& start, const Vector3& end);
	// Get point along segment where 0 <= t <= 1
	Vector3 PointOnSegment(float t) const;
	// Get minimum distance squared between point and line segment
	float MinDistSq(const Vector3& point) const;
	// Get MinDistSq between two line segments
	static float MinDistSq(const LineSegment& s1, const LineSegment& s2);

	Vector3 mStart;
	Vector3 mEnd;
};
