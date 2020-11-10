#include "Scene.h"
#include "../Game.h"
#include "../Actor/Actor.h"

Scene::Scene(const std::weak_ptr<class Game>& game)
	: mGame(game)
{

}

Scene::~Scene()
{

}

void Scene::processInput()
{

}

void Scene::update()
{

}

void Scene::draw()
{

}

void Scene::addActor(const std::shared_ptr<class Actor>& actor)
{

}

void Scene::removeActor(const std::weak_ptr<class Actor>& actor)
{

}