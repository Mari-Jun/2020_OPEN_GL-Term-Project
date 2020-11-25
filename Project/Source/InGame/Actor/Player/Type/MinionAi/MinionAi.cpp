#include "MinionAi.h"
#include "../../../../Map/GameMap.h"
#include "../../../../Actor/Tile/Tile.h"
#include "../../../../../Game/Scene/Scene.h"
#include <algorithm>

bool MinionAi::isInside(int y, int x)
{
	if (y < 0) return false;
	if (y > 19) return false;
	if (x < 0) return false;
	if (x > 19) return false;
	if (mWaypoint[y][x].visit == 1) return false;
	if (!(mWaypoint[y][x].type == int(Tile::Type::Road) || 
		mWaypoint[y][x].type == int(Tile::Type::EndPoint) ||
		mWaypoint[y][x].type == int(Tile::Type::Light))) return false;

	return true;
}


void MinionAi::BFS()
{
	std::pair<int, int> start, end;

	start.first = startPoint.first;
	start.second = startPoint.second;
	end = endPoint;

	BFS_INFO b;
	b.b_pos = start;
	b.visit = 1;


	mWaypoint[start.first][start.second].visit = 1;
	mWaypoint[start.first][start.second].b_pos = start;	//첫부분은 자기자신이 이전좌표/ 

	BFSqueue.push(b.b_pos);
	while (!BFSqueue.empty()) {

		b.b_pos = BFSqueue.front();
		BFSqueue.pop();

		if (mWaypoint[b.b_pos.first][b.b_pos.second].type == int(Tile::Type::EndPoint))
		{
			while (!BFSqueue.empty())
				BFSqueue.pop();
			break;
		}

		for (int i = 0; i < 4; ++i)
		{
			int next_y = b.b_pos.first + dir[i][0];		//다음 갈곳 탐색
			int next_x = b.b_pos.second + dir[i][1];

			if (isInside(next_y, next_x))
			{
				mWaypoint[next_y][next_x].visit = 1;			//들를곳이 맞으면 visit 채워주고 
				mWaypoint[next_y][next_x].b_pos = b.b_pos;	//이전좌표를 넣어줌
				BFSqueue.push(std::pair(next_y, next_x));
			}
		}
	}

	result = end;
	while (1)
	{
		if (result == startPoint)
			break;
		MinWay.push_back(mWaypoint[result.first][result.second].b_pos);
		result = mWaypoint[result.first][result.second].b_pos;
	}
	std::reverse(MinWay.begin(), MinWay.end());
}

MinionAi::MinionAi(const std::weak_ptr<class Scene>& scene)
	:
	mScene(scene)
{

}

void MinionAi::initailize
(
	const std::vector<std::vector<std::weak_ptr<class Tile>>> mTile,
	std::pair<int, int> start,
	std::pair<int, int> end,
	float mTileSize,
	int mMapSize
)
{
	mAiMap = mTile;
	startPoint = start;
	endPoint = end;
	TileSize = mTileSize;
	MapSize = mMapSize;

	BFS_INFO tmp;
	for (int i = 0; i < mAiMap.size(); ++i)
	{
		mWaypoint.resize(mAiMap.size(), std::vector<class BFS_INFO>(mAiMap[i].size()));
	}

	for (auto i = 0; i < mAiMap.size(); ++i)
	{
		for (auto j = 0; j < mAiMap[i].size(); ++j)
		{
			mWaypoint[i][j].type = int(mAiMap[i][j].lock()->getType());
		}
	}

	BFS();


}
MinionAi::MinionAi(const std::weak_ptr<class Scene>& scene, const std::vector<std::vector<std::weak_ptr<class Tile>>> mTile, std::pair<int, int> start, std::pair<int, int>end)
	:
	mScene(scene),
	mAiMap(mTile),
	startPoint(start),
	endPoint(end)
{
	//mAiMap[0][0].lock()->getType();
	BFS_INFO tmp;
	for (int i = 0; i < mAiMap.size(); ++i)
	{
		mWaypoint.resize(mAiMap.size(), std::vector<class BFS_INFO>(mAiMap[i].size()));
	}

	for (auto i = 0; i < mAiMap.size(); ++i)
	{
		for (auto j = 0; j < mAiMap[i].size(); ++j)
		{
			mWaypoint[i][j].type = int(mAiMap[i][j].lock()->getType());
		}
	}

	BFS();
}

MinionAi::~MinionAi()
{

}
