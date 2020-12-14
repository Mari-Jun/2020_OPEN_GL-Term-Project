#include "Particle.h"
#include "../../../Game/Component/MoveComponent.h"
#include "../../../Game/Graphics/Mesh/BillBoardComponent.h"
#include "../../../Game/Actor/Defualt/DefualtShape.h"
#include "../../../Game/Game.h"

Particle::Particle(const std::weak_ptr<class Scene>& scene, const std::string& season)
	: Actor(scene)
	, mSeason(season)
{

}

Particle::~Particle()
{

}

void Particle::initailize()
{
	Actor::initailize();

	//Create Particle~
	auto fileName = "Asset/Image/Particle/" + mSeason + ".png";
	mParticle = std::make_shared<BillBoardComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mParticle->initailize();
	mParticle->setTexture(getGame().lock()->getRenderer()->getTexture(fileName));

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();
}

void Particle::updateActor(float deltatime)
{
	float gravitySpeed = -200.0f;

	mMoveComponent->setUpSpeed(gravitySpeed);

	if (getPosition().y <= -30.0f)
	{
		setState(State::Dead);
	}
}

void Particle::actorInput()
{

}