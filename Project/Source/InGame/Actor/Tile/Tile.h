#pragma once
#include "../../../Game/Actor/Actor.h"

class Tile : public Actor
{
public:
	enum class TileType
	{
		Basic, Road, Light,
		Rock, Hill, Crystal,
		Tree, TreeDouble, TreeQuad,
		StartPoint, EndPoint,	
		Tower_RoundA, Tower_RoundC, Tower_Blaster,
		Tower_SquareA, Tower_SquareB, Tower_SquareC,
		Tower_Ballista, Tower_Cannon, Tower_Catapult
	};

	enum class SeasonType
	{
		Sakura, Green, Maple, Snow
	};

	Tile(const std::weak_ptr<class Scene>& scene, TileType type = TileType::Basic);
	virtual ~Tile() noexcept;

	virtual void initailize() override;

	std::shared_ptr<class Mesh> loadMesh() const;

private:
	TileType mType;
	SeasonType mSeasonType;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class BoxComponent> mBoxComponent;

public:
	TileType getTileType() const { return mType; }
	std::string getTileTypeToString() const;
	const std::shared_ptr<class BoxComponent>& getBoxComponent() const { return mBoxComponent; }
	std::string getSeasonTypeToString() const;
	void setSeasonType(SeasonType type) { mSeasonType = type; }
};