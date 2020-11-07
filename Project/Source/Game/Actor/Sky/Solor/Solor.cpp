#include "Solor.h"
#include "../../../Graphics/Window.h"
#include "../../../Game.h"
#include "../../../Component/MoveComponent.h"
#include "../../Defualt/DefualtShape.h"

Solor::Solor(const std::weak_ptr<class Game>& game)
	: Actor(game)
{

}

Solor::~Solor()
{

}

void Solor::initailize()
{
	Actor::initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create Planets
	mPlanets.resize(3);
	mPlanets[0] = std::make_shared<DefualtShape>(getGame(), DefualtShape::Shape::Sphere, false);
	mPlanets[0]->setMeshColor(Vector3::Rgb(Vector3(256.0f, 0.0f, 0.0f)));
	mPlanets[0]->setScale(20.0f);
	mPlanets[0]->setPosition(getPosition() + getSide() * 75.0f);
	mPlanets[0]->initailize();

	mPlanets[1] = std::make_shared<DefualtShape>(getGame(), DefualtShape::Shape::Sphere, false);
	mPlanets[1]->setMeshColor(Vector3::Rgb(Vector3(0.0f, 256.0f, 0.0f)));
	mPlanets[1]->setScale(10.0f);
	mPlanets[1]->setPosition(getPosition() + getSide() * 150.0f);
	mPlanets[1]->initailize();

	mPlanets[2] = std::make_shared<DefualtShape>(getGame(), DefualtShape::Shape::Sphere, false);
	mPlanets[2]->setMeshColor(Vector3::Rgb(Vector3(0.0f, 0.0f, 256.0f)));
	mPlanets[2]->setScale(5.0f);
	mPlanets[2]->setPosition(getPosition() + getSide() * 200.0f);
	mPlanets[2]->initailize();
}

void Solor::updateActor(float deltatime)
{
	Vector3 dist = mPlanets[0]->getPosition() - getPosition();
	dist = Vector3::Transform(dist, Quaternion(getUp(), Math::ToRadians(1)));
	mPlanets[0]->setPosition(getPosition() + dist);

	dist = mPlanets[1]->getPosition() - getPosition();
	dist = Vector3::Transform(dist, Quaternion(getUp(), Math::ToRadians(1.5)));
	mPlanets[1]->setPosition(getPosition() + dist);

	dist = mPlanets[2]->getPosition() - getPosition();
	dist = Vector3::Transform(dist, Quaternion(getUp(), Math::ToRadians(2)));
	mPlanets[2]->setPosition(getPosition() + dist);
}

void Solor::actorInput()
{

}