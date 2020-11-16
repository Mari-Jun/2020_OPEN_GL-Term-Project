#include "Bow.h"
#include "../../../../Game/Game.h"

Bow::Bow(const std::weak_ptr<class Scene>& scene)
	: EnemyTower(scene, EnemyTower::Type::Ballista_Bow)
{
	std::cout << "³­Á×ÅÃ\n";
}

Bow::~Bow()
{
	std::cout << "³­Á×ÅÃ\n";
}

void Bow::initailize()
{
	EnemyTower::initailize();
}

void Bow::updateActor(float deltatime)
{
	auto a = chasePlayer();
	auto b = getForward();
	a.x = 0.0f;
	b.x = 0.0f;
	a.Normalize();
	b.Normalize();

	auto rad = Math::Acos(Vector3::Dot(a, b));

	if (!Math::NearZero(rad))
	{
		if (Vector3::Cross(a, b).y < 0.0f)
			rad *= -1;

		std::cout << rad << std::endl;

		//setRotation(Quaternion::Slerp(getRotation(), Quaternion::Concatenate(getRotation(), Quaternion(getSide(), rad)), 0.1f));
		//setRotation(Quaternion::Concatenate(getRotation(), Quaternion(getSide(), rad)));
	}


}

void Bow::actorInput()
{

}