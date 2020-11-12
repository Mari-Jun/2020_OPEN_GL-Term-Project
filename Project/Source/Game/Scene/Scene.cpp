#include "Scene.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Etc/DeltaTime.h"
#include "../Actor/Actor.h"

Scene::Scene(const std::weak_ptr<class Game>& game)
	: mState(State::Active)
	, mGame(game)
	, mIsUpdateActor(false)
{
	
}

Scene::~Scene()
{
	mGame.lock()->removeScene(weak_from_this());
}

void Scene::initailize()
{
	mGame.lock()->addScene(shared_from_this());
}

void Scene::sceneInput()
{
	mGame.lock()->getRenderer()->processInput();

	mIsUpdateActor = true;
	for (auto actor : mActors)
	{
		actor.second->processInput();
	}
	mIsUpdateActor = false;
}

void Scene::sceneUpdate(float deltatime)
{
	mIsUpdateActor = true;
	std::cout << mActors.size() << std::endl;
	for (auto actor : mActors)
	{
		actor.second->update(deltatime);
	}
	mIsUpdateActor = false;

	for (auto actor : mReadyActors)
	{
		actor.second->updateWorldTransform();
		mActors.emplace(actor);
	}
	mReadyActor.clear();

	std::vector<std::shared_ptr<Actor>> deadActor;
	for (auto& actor : mActors)
	{
		if (actor.second->getState() == Actor::State::Dead)
		{
			deadActor.emplace_back(std::move(actor.second));
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

void Scene::addActor(const std::string& type, const std::shared_ptr<class Actor>& actor)
{
	if (mIsUpdateActor)
	{
		mReadyActors.insert(std::make_pair(type, actor));
	}
	else
	{
		mActors.insert(std::make_pair(type, actor));
	}
}

void Scene::removeActor(const std::string& type, const std::weak_ptr<class Actor>& actor)
{
	auto iter = std::find_if(mReadyActors.begin(), mReadyActors.end(),
		[&actor](const std::pair<std::string, std::weak_ptr<class Actor>>& act)
		{return actor.lock() == act.second.lock(); });
	if (iter != mReadyActors.end())
	{
		mReadyActors.erase(iter);
	}
	
	iter = std::find_if(mActors.begin(), mActors.end(),
		[&actor](const std::pair<std::string, std::weak_ptr<class Actor>>& act)
		{return actor.lock() == act.second.lock(); });
	if (iter != mActors.end())
	{
		mActors.erase(iter);
	}
}