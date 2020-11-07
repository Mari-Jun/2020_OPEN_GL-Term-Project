#pragma once
#include "../../Math/Math.h"
#include <vector>

struct ConvexPolygon
{
	bool Contains(const Vector2& point) const;
	// Vertices have a clockwise ordering
	std::vector<Vector2> mVertices;
};