#pragma once
#include "../../../Game/Actor/Actor.h"

class Tile : public Actor
{
public:
	enum class Type
	{
		Basic, Road,
		Rock, Hill, Crystal,
		Tree, TreeDouble, TreeQuad,
		StartPoint, EndPoint, Snow_Basic,
		Snow_Rock, Snow_Hill, Snow_Crystal,
		Snow_Tree, Snow_TreeDouble, Snow_TreeQuad
	};

	Tile(const std::weak_ptr<class Game>& game, Type type = Type::Basic);
	virtual ~Tile() noexcept;

	virtual void initailize() override;

	virtual void updateActor(float deltatime) override;
	virtual void actorInput() override;

	std::shared_ptr<class Mesh> loadMesh() const;

private:
	Type mType;
	std::shared_ptr<class MeshComponent> mMeshComponent;
	std::shared_ptr<class BoxComponent> mBoxComponent;

public:
	Type getType() const { return mType; }
	std::string getTypeToString() const;
};