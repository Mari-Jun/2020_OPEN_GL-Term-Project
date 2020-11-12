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

	float closestT = Math::Infinity;
	Vector3 norm;

	for (const auto& boxes : mBoxes)
	{
		for (const auto& box : boxes.second)
		{
			float t;

			if (Intersect(l, box.lock()->getWorldBox(), t, norm))
			{
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
	}
	return collided;
}

void PhysEngine::TestPairwise(std::function<void(std::weak_ptr<class Actor>&, std::weak_ptr<class Actor>&)> f)
{
	for (auto boxes : mBoxes)
	{
		for (size_t i = 0; i < boxes.second.size(); i++)
		{
			for (size_t j = i + 1; j < boxes.second.size(); j++)
			{
				std::weak_ptr<BoxComponent>& a = boxes.second[i];
				std::weak_ptr<BoxComponent>& b = boxes.second[j];
				if (Intersect(a.lock()->getWorldBox(), b.lock()->getWorldBox()))
				{
					f(a.lock()->getOwner(), b.lock()->getOwner());
				}
			}
		}
	}
	
}

void PhysEngine::TestSweepAndPrune(std::function<void(std::weak_ptr<Actor>&, std::weak_ptr<Actor>&)> f)
{
	// Sort by min.x
	for (auto boxes : mBoxes)
	{
		std::sort(boxes.second.begin(), boxes.second.end(),
			[](std::weak_ptr<BoxComponent>& a, std::weak_ptr<BoxComponent>& b) {
				return a.lock()->getWorldBox().mMin.x <
					b.lock()->getWorldBox().mMin.x;
			});

		for (size_t i = 0; i < boxes.second.size(); i++)
		{
			std::weak_ptr<BoxComponent>& a = boxes.second[i];
			float max = a.lock()->getWorldBox().mMax.x;
			for (size_t j = i + 1; j < boxes.second.size(); j++)
			{
				std::weak_ptr<BoxComponent>& b = boxes.second[j];

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
}

void PhysEngine::addBox(const std::string& type, const std::weak_ptr<class BoxComponent>& box)
{
	auto iter = mBoxes.find(type);
	if (iter == mBoxes.end())
	{
		std::vector<std::weak_ptr<class BoxComponent>> ret;
		ret.emplace_back(box);
		mBoxes.insert({ type,ret });
	}
	else
	{
		iter->second.emplace_back(box);
	}
}

void PhysEngine::removeBox(const std::string& type, const std::weak_ptr<class BoxComponent>& box)
{
	auto Boxes = mBoxes.find(type);
	if (Boxes != mBoxes.end())
	{
		auto& boxes = Boxes->second;
		auto iter = std::find_if(boxes.begin(), boxes.end(),
			[&box](const std::weak_ptr<class BoxComponent>& bx)
			{return box.lock() == bx.lock(); });
		if (iter != boxes.end())
		{
			std::iter_swap(iter, boxes.end() - 1);
			boxes.pop_back();
		}
	}
}
	