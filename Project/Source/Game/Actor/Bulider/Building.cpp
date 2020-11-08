#include <random>
#include "Building.h"
#include "../../Graphics/Window.h"
#include "../../Game.h"
#include "../Defualt/AlphaShape.h"


Building::Building(const std::weak_ptr<class Game>& game)
	: Actor(game)
{

}

Building::~Building()
{

}

void Building::initailize()
{
	Actor::initailize();

	for (auto count = 0; count < 10; count++)
	{
		std::random_device rd;
		std::mt19937 mersenne(rd());
		std::uniform_int_distribution<> pos(150, 400);
		std::uniform_int_distribution<> mi(0, 3);
		std::uniform_int_distribution<> size(25, 50);
		std::uniform_int_distribution<> color(0, 256);

		//Create Snow~
		auto buliding = std::make_shared<AlphaShape>(getGame(), AlphaShape::Shape::Box);
		buliding->setScale(Vector3(size(mersenne), 3 * size(mersenne), size(mersenne)));

		auto x = pos(mersenne) * (mi(mersenne) == 0 ? -1 : 1);
		auto y = buliding->getScale().y / 2;
		auto z = pos(mersenne) * (mi(mersenne) == 0 ? -1 : 1);
		std::cout << x << ", " << y << ", " << z << std::endl;
		Vector3 p(x, y, z);
		buliding->setPosition(getPosition() + p);

		buliding->setMeshColor(Vector3::Rgb(Vector3(color(mersenne), color(mersenne), color(mersenne))));
		buliding->initailize();
	}
}

void Building::updateActor(float deltatime)
{
	
}

void Building::actorInput()
{
	auto game = getGame().lock();
}