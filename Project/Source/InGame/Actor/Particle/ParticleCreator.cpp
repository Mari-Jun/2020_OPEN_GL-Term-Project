#include "ParticleCreator.h"
#include "Particle.h"
#include "../../../Game/Game.h"
#include "../../../Game/Input/KeyBoard.h"
#include <random>

ParticleCreator::ParticleCreator(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Actor>& follower, const std::string& season)
	: Actor(scene)
	, mFollower(follower)
	, mSeason(season)
{
	
}

ParticleCreator::~ParticleCreator()
{

}

void ParticleCreator::initailize()
{
	Actor::initailize();
}

void ParticleCreator::updateActor(float deltatime)
{
	const auto& pos = mFollower.lock()->getPosition();
	setPosition(Vector3(pos.x, getPosition().y, pos.z));

	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> newPos(static_cast<int>(-getScale().x), static_cast<int>(getScale().x));
	std::uniform_int_distribution<> newRot(0, 359);

	for (auto i = 0; i < 3; i++)
	{
		auto particle = std::make_shared<Particle>(getScene(), mSeason);
		particle->setPosition(getPosition() + Vector3(static_cast<float>(newPos(mersenne)), 0.0f, static_cast<float>(newPos(mersenne))));
		particle->setScale(0.03f);
		particle->setRotation(Quaternion(Vector3::UnitZ, Math::ToRadians(static_cast<float>(newRot(mersenne)))));
		particle->initailize();
	}
}

void ParticleCreator::actorInput()
{

}