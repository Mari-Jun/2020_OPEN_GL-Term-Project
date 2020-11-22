#pragma once
#pragma once
#include <queue>
#include <memory>


struct BFS_INFO {
	int visit = 0;
	std::pair<int, int> b_pos = std::pair(-1, -1);
	int type;
};

//struct BFS_INFO map[20][20];




class MinionAi : public std::enable_shared_from_this<MinionAi>
{
public:
	MinionAi(
		const std::weak_ptr<class Scene>& scene,
		const std::vector<std::vector<std::weak_ptr<class Tile>>> mTile,
		std::pair<int, int> start,
		std::pair<int, int> end
	);
	MinionAi(const std::weak_ptr<class Scene>& scene);
	~MinionAi();
	void BFS();
	bool isInside(int y, int x);

private:
	float TileSize;
	int MapSize;
	std::weak_ptr<class Scene> mScene;
	std::pair<int, int> startPoint, endPoint;
	std::vector<std::vector<std::weak_ptr<class Tile>>> mAiMap;	// GameMap ���� �޾ƿ��� ���� �� ����
	std::vector<std::vector<class BFS_INFO>> mWaypoint;	// GameMap ���� �ʿ��Ѱ� (Tile ����)�� ���ͼ� �ٽ� ����
	std::vector<std::pair<int, int>> MinWay;		//�����
	int dir[4][2] = { {-1,0},{0,-1},{0,1},{1,0} };	//8���� , 4�������� ���� �� ���ɼ� ������
	std::queue<std::pair<int, int>> BFSqueue;	//BFS�� ���� queue
	std::pair<int, int> result;					//������� �ֱ� ���� tmp

public:
	void initailize(const std::vector<std::vector<std::weak_ptr<class Tile>>> mTile,
		std::pair<int, int> start,
		std::pair<int, int> end,
		float mTileSize,
		int mMapSize
	);
	std::vector<std::pair<int, int>> getMinway() { return MinWay; }
	float getTileSize() const { return TileSize; }
	int getMapSize() const { return MapSize; }
	//std::weak_ptr<class MinionAi>& getAiMap() { return const_cast<std::weak_ptr<class MinionAi>&>(std::as_const(*this).getAiMap()); }

};