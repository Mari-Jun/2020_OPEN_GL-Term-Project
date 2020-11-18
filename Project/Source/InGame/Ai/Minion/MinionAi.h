#pragma once
#include <queue>
#include <memory>


struct BFS_INFO {
	int visit = 0;
	std::pair<int, int> b_pos = std::pair(-1,-1);
	int type;
};

//struct BFS_INFO map[20][20];




class MinionAi : public std::enable_shared_from_this<MinionAi>
{
public:
	MinionAi(const std::vector<std::vector<std::weak_ptr<class Tile>>> mTile, std::pair<int, int> start, std::pair<int, int> end);
	~MinionAi();
	void BFS();
	bool isInside(int y, int x);

private:
	std::pair<int, int> startPoint, endPoint;
	std::vector<std::vector<std::weak_ptr<class Tile>>> mAiMap;	// GameMap 에서 받아오는 현재 맵 정보
	std::vector<std::vector<class BFS_INFO>> mWaypoint;	// GameMap 에서 필요한것 (Tile 정보)만 빼와서 다시 저장
	std::vector<std::pair<int, int>> MinWay;		//결과값
	int dir[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };	//8방향 , 4방향으로 수정 될 가능성 농후함
	std::queue<std::pair<int, int>> BFSqueue;	//BFS를 위한 queue
	std::pair<int, int> result;					//결과값에 넣기 위한 tmp


};