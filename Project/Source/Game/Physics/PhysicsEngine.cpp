#include "PhysicsEngine.h"
#include <algorithm>
#include "../Component/BoxComponent.h"

PhysEngine::PhysEngine(const std::weak_ptr<class Game>& game)
	: mGame(game)
{

}

PhysEngine::~PhysEngine()
{

}

bool PhysEngine::segmentCast(const LineSegment& l, CollisionInfo& outColl)
{
	bool collided = false;
	// Initialize closestT to infinity, so first
	// intersection will always update closestT
	float closestT = Math::Infinity;
	Vector3 norm;
	// Test against all boxes
	for (auto box : mBoxes)
	{
		float t;
		// Does the segment intersect with the box?
		if (Intersect(l, box.lock()->getWorldBox(), t, norm))
		{
			// Is this closer than previous intersection?
			if (t < closestT)
			{
				outColl.mPoint = l.PointOnSegment(t);
				outColl.mNormal = norm;
				outColl.mBox = box;
				outColl.mActor = box.lock()->getOwner();
				collided = true;
			}
		}
	}
	return collided;
}

void PhysEngine::TestPairwise(std::function<void(std::weak_ptr<class Actor>&, std::weak_ptr<class Actor>&)> f)
{
	// Naive implementation O(n^2)
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// Don't need to test vs itself and any previous i values
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			std::weak_ptr<BoxComponent>& a = mBoxes[i];
			std::weak_ptr<BoxComponent>& b = mBoxes[j];
			if (Intersect(a.lock()->getWorldBox(), b.lock()->getWorldBox()))
			{
				// Call supplied function to handle intersection
				f(a.lock()->getOwner(), b.lock()->getOwner());
			}
		}
	}
}

void PhysEngine::TestSweepAndPrune(std::function<void(std::weak_ptr<Actor>&, std::weak_ptr<Actor>&)> f)
{
	// Sort by min.x
	std::sort(mBoxes.begin(), mBoxes.end(),
		[](std::weak_ptr<BoxComponent>& a, std::weak_ptr<BoxComponent>& b) {
			return a.lock()->getWorldBox().mMin.x <
				b.lock()->getWorldBox().mMin.x;
		});

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// Get max.x for current box
		std::weak_ptr<BoxComponent>& a = mBoxes[i];
		float max = a.lock()->getWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			std::weak_ptr<BoxComponent>& b = mBoxes[j];
			// If AABB[j] min is past the max bounds of AABB[i],
			// then there aren't any other possible intersections
			// against AABB[i]
			if (b.lock()->getWorldBox().mMin.x > max)
			{
				break;
			}
			else if (Intersect(a.lock()->getWorldBox(), b.lock()->getWorldBox()))
			{
				f(a.lock()->getOwner(), b.lock()->getOwner());
			}
		}
	}
}

void PhysEngine::addBox(const std::weak_ptr<class BoxComponent>& box)
{
	mBoxes.emplace_back(box);
}

void PhysEngine::removeBox(const std::weak_ptr<class BoxComponent>& box)
{
	auto iter = std::find_if(mBoxes.begin(), mBoxes.end(),
		[&box](const std::weak_ptr<BoxComponent>& bComp)
		{return box.lock() == bComp.lock(); });
	if (iter != mBoxes.end())
	{
		mBoxes.erase(iter);
	}
}