#include "EndPointTile.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"
#include "../Player/Player.h"
#include "../../Scene/GameScene.h"
#include "../Player/Type/DefaultMinion.h"

EndPointTile::EndPointTile(const std::weak_ptr<class Scene>& scene)
	: Tile(scene, TileType::EndPoint)
{

}

EndPointTile::~EndPointTile()
{

}

void EndPointTile::initailize()
{
	Tile::initailize();
}

void EndPointTile::updateActor(float deltatime)
{
	collidePlayers();
}

void EndPointTile::collidePlayers()
{
	updateWorldTransform();

	AABB endBox = getBoxComponent()->getWorldBox();

	const auto& allBoxes = getGame().lock()->getPhysEngine()->getBoxes();
	auto boxes = allBoxes.find(getTypeToString(Type::Player));
	if (boxes != allBoxes.end())
	{
		for (const auto& b : boxes->second)
		{
			const AABB& objectBox = b.lock()->getWorldBox();
			auto objectOwner = std::dynamic_pointer_cast<Player>(b.lock()->getOwner().lock());

			if (shared_from_this() != objectOwner && Intersect(endBox, objectBox))
			{
				if (objectOwner->getPlayerType() == PlayerInfo::PlayerType::Control)
				{
					auto gameScene = std::dynamic_pointer_cast<GameScene>(getScene().lock());
					gameScene->stageClear();
				}
				else
				{
					auto minion = std::dynamic_pointer_cast<DefaultMinion>(objectOwner);
					minion->endPoint();
				}
			}
		}
	}
}