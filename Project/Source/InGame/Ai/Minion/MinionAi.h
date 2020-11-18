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
	std::vector<std::vector<std::weak_ptr<class Tile>>> mAiMap;	// GameMap ���� �޾ƿ��� ���� �� ����
	std::vector<std::vector<class BFS_INFO>> mWaypoint;	// GameMap ���� �ʿ��Ѱ� (Tile ����)�� ���ͼ� �ٽ� ����
	std::vector<std::pair<int, int>> MinWay;		//�����
	int dir[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };	//8���� , 4�������� ���� �� ���ɼ� ������
	std::queue<std::pair<int, int>> BFSqueue;	//BFS�� ���� queue
	std::pair<int, int> result;					//������� �ֱ� ���� tmp


};