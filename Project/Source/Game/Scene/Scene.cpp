#include "Scene.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Etc/DeltaTime.h"
#include "../Actor/Actor.h"

Scene::Scene(const std::weak_ptr<class Game>& game)
	: mGame(game)
{

}

Scene::~Scene()
{

}

void Scene::sceneInput()
{
	mGame.lock()->getRenderer()->processInput();

	mIsUpdateActor = true;
	for (auto actor : mActor)
	{
		actor->processInput();
	}
	mIsUpdateActor = false;
}

void Scene::sceneUpdate(float deltatime)
{
	mIsUpdateActor = true;
	for (auto actor : mActor)
	{
		actor->update(deltatime);
	}
	mIsUpdateActor = false;

	for (auto actor : mReadyActor)
	{
		actor->updateWorldTransform();
		mActor.emplace_back(actor);
	}
	mReadyActor.clear();

	std::vector<std::shared_ptr<Actor>> deadActor;
	for (auto& actor : mActor)
	{
		if (actor->getState() == Actor::State::Dead)
		{
			deadActor.emplace_back(std::move(actor));
		}
	}

	for (auto& actor : deadActor)
	{
		actor.reset();
	}
	deadActor.clear();

	mGame.lock()->getRenderer()->update(deltatime);
}

void Scene::draw()
{
	mGame.lock()->getRenderer()->draw();
}

void Scene::loadData()
{

}

void Scene::unLoadData()
{

}

void Scene::addActor(const std::shared_ptr<class Actor>& actor)
{
	if (mIsUpdateActor)
	{
		mReadyActor.emplace_back(actor);
	}
	else
	{
		mActor.emplace_back(actor);
	}
}

void Scene::removeActor(const std::weak_ptr<class Actor>& actor)
{
	auto iter = std::find_if(mReadyActor.begin(), mReadyActor.end(),
		[&actor](const std::weak_ptr<Actor>& act)
		{return actor.lock() == act.lock(); });
	if (iter != mReadyActor.end())
	{
		std::iter_swap(iter, mReadyActor.end() - 1);
		mReadyActor.pop_back();
	}

	iter = std::find_if(mActor.begin(), mActor.end(),
		[&actor](const std::weak_ptr<Actor>& act)
		{return actor.lock() == act.lock(); });
	if (iter != mActor.end())
	{
		std::iter_swap(iter, mActor.end() - 1);
		mActor.pop_back();
	}
}