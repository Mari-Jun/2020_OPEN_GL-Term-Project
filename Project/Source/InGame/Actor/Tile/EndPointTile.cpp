#include "EndPointTile.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"

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

}

void EndPointTile::collidePlayers()
{
	/*updateWorldTransform();

	AABB endBox = getBoxComponent()->getWorldBox();
	Vector3 pos = getPosition();

	auto allBoxes = getGame().lock()->getPhysEngine()->getBoxes();
	auto boxes = allBoxes.find(getTypeToString(Actor::Type::Player));
	if (boxes != allBoxes.end())
	{
		for (auto b : boxes->second)
		{
			const AABB& box = b.lock()->getWorldBox();
			const auto& boxActor = b.lock()->getOwner();

			if (shared_from_this() != boxActor.lock() && Intersect(robotBox, box))
			{
				float dx1 = box.mMax.x - robotBox.mMin.x;
				float dx2 = box.mMin.x - robotBox.mMax.x;
				float dy1 = box.mMax.y - robotBox.mMin.y;
				float dy2 = box.mMin.y - robotBox.mMax.y;
				float dz1 = box.mMax.z - robotBox.mMin.z;
				float dz2 = box.mMin.z - robotBox.mMax.z;

				float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
				float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
				float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

				if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
				{
					pos.x += dx;
				}
				if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
				{
					pos.y += dy;
					mGravitySpeed = 0.0f;
				}
				if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
				{
					pos.z += dz;
				}

				setPosition(pos);
				mBoxComponent->updateWorldTransForm();
			}
		}
	}*/
}