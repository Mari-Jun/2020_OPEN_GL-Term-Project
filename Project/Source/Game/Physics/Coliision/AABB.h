#pragma once
#include "../../Math/Math.h"

struct AABB
{
	AABB(const Vector3& min, const Vector3& max);
	// Update min and max accounting for this point
	// (used when loading a model)
	void UpdateMinMax(const Vector3& point);
	// Rotated by a quaternion
	void Rotate(const Quaternion& q);
	bool Contains(const Vector3& point) const;
	float MinDistSq(const Vector3& point) const;

	Vector3 mMin;
	Vector3 mMax;
};