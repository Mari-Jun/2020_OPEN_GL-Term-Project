#pragma once
#include <memory>
#include <functional>
#include <vector>
#include "../Math/Math.h"
#include "Coliision/Collision.h"

class PhysEngine : public std::enable_shared_from_this<PhysEngine>
{
public:
	PhysEngine(const std::weak_ptr<class Game>& game);
	~PhysEngine();

	struct CollisionInfo
	{
		//�浹 ����
		Vector3 mPoint;
		//�浹 ���� ���� ����
		Vector3 mNormal;
		//�浹�� �ڽ�
		std::weak_ptr<class BoxComponent> mBox;
		//�浹�� ����
		std::weak_ptr<class Actor> mActor;
	};

	bool segmentCast(const LineSegment& l, CollisionInfo& outColl);
	void TestPairwise(std::function<void(std::weak_ptr<class Actor>&, std::weak_ptr<class Actor>&)> f);
	void TestSweepAndPrune(std::function<void(std::weak_ptr<class Actor>&, std::weak_ptr<class Actor>&)> f);

	void addBox(const std::weak_ptr<class BoxComponent>& box);
	void removeBox(const std::weak_ptr<class BoxComponent>& box);

	std::vector<std::weak_ptr<class BoxComponent>>& getBoxes() { return mBoxes; }

private:
	std::weak_ptr<class Game> mGame;
	std::vector<std::weak_ptr<class BoxComponent>> mBoxes;
};