#include "Scene.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Game.h"
#include "../Actor/Actor.h"
#include "../UI/UI.h"

Scene::Scene(const std::weak_ptr<class Game>& game)
	: mState(SceneState::Active)
	, mGame(game)
	, mIsUpdateActor(false)
{
	
}

Scene::~Scene()
{
	for (auto& actors : mReadyActors)
	{
		for (auto& actor : actors.second)
		{
			actor.reset();
		}
	}
	mReadyActors.clear();
	for (auto& actors : mActors)
	{
		for (auto& actor : actors.second)
		{
			actor.reset();
		}
	}
	mActors.clear();

	for (auto& ui : mUserInterfaces)
	{
		ui.reset();
	}
	mUserInterfaces.clear();

	mGame.lock()->removeScene(weak_from_this());
}

void Scene::initailize()
{
	mGame.lock()->addScene(shared_from_this());
}

void Scene::processInput()
{
	if (mState == SceneState::Active)
	{
		sceneInput();
	}
	uiInput();
}
void Scene::sceneInput()
{
	mGame.lock()->getRenderer()->processInput();

	mIsUpdateActor = true;

	for (const auto& actors : mActors)
	{
		for (const auto& actor : actors.second)
		{
			actor->processInput();
		}
	}
	mIsUpdateActor = false;	
}

void Scene::uiInput()
{
	if (!mUserInterfaces.empty() &&
		mUserInterfaces.back()->getState() == UI::UIState::Active)
	{
		mUserInterfaces.back()->processInput();
	}
}

void Scene::update()
{
	static int Fps = 0;
	static int oldTime = 0;
	static int fpsTime = 0;
	int time = glutGet(GLUT_ELAPSED_TIME);
	float deltatime = (time - oldTime) / 1000.0f;

	if (deltatime >= 0.016f)
	{
		oldTime = time;
		Fps++;

		if (time - fpsTime > 1000)
		{
			std::cout << "ÇÁ·¹ÀÓ : " << Fps << std::endl;
			Fps = 0;
			fpsTime = time;
		}

		uiUpdate(deltatime);

		if (mState == Scene::SceneState::Active)
		{
			sceneUpdate(deltatime);
		}
		
	}
}

void Scene::sceneUpdate(float deltatime)
{
	mIsUpdateActor = true;
	for (const auto& actors : mActors)
	{
		for (const auto& actor : actors.second)
		{
			actor->update(deltatime);
		}
	}
	mIsUpdateActor = false;

	for (const auto& actors : mReadyActors)
	{
		for (const auto& actor : actors.second)
		{
			actor->updateWorldTransform();
			mActors.find(actors.first)->second.emplace_back(actor);
		}
	}
	mReadyActors.clear();

	mIsUpdateActor = true;

	std::unordered_map<std::string, std::vector<std::shared_ptr<class Actor>>> deadActor;
	for (auto& actors : mActors)
	{
		for (auto& actor : actors.second)
		{
			if (actor->getState() == Actor::State::Dead)
			{
				auto iter = deadActor.find(actors.first);
				if (iter == deadActor.end())
				{
					std::vector<std::shared_ptr<class Actor>> ret;
					ret.emplace_back(std::move(actor));
					deadActor.insert({ actors.first, ret });
				}
				else
				{
					iter->second.emplace_back(std::move(actor));
				}
			}
		}
	}

	for (auto& actors : deadActor)
	{
		for (auto& actor : actors.second)
		{
			actor.reset();
		}
	}
	deadActor.clear();

	mIsUpdateActor = false;

	mGame.lock()->getRenderer()->update(deltatime);
}

void Scene::uiUpdate(float deltatime)
{
	for (const auto& ui : mUserInterfaces)
	{
		if (ui->getState() == UI::UIState::Active)
		{
			ui->update(deltatime);
		}
	}

	auto iter = mUserInterfaces.begin();
	while (iter != mUserInterfaces.end())
	{
		if ((*iter)->getState() == UI::UIState::Dead)
		{
			iter = mUserInterfaces.erase(iter);
		}
		else
		{
			++iter;
		}
	}
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

void Scene::addActor(const std::string& type, const std::shared_ptr<class Actor>& actor)
{
	if (mIsUpdateActor)
	{
		auto iter = mReadyActors.find(type);
		if (iter == mReadyActors.end())
		{
			std::vector<std::shared_ptr<class Actor>> ret;
			ret.emplace_back(actor);
			mReadyActors.insert({ type,ret });
		}
		else
		{
			iter->second.emplace_back(actor);
		}
	}
	else
	{
		auto iter = mActors.find(type);
		if (iter == mActors.end())
		{
			std::vector<std::shared_ptr<class Actor>> ret;
			ret.emplace_back(actor);
			mActors.insert({ type,ret });
		}
		else
		{
			iter->second.emplace_back(actor);
		}
	}
}

void Scene::removeActor(const std::string& type, const std::weak_ptr<class Actor>& actor)
{
	auto rActors = mReadyActors.find(type);
	if (rActors != mReadyActors.end())
	{
		auto& actors = rActors->second;
		auto iter = std::find_if(actors.begin(), actors.end(),
			[&actor](const std::weak_ptr<Actor>& act)
			{return actor.lock() == act.lock(); });
		if (iter != actors.end())
		{
			std::iter_swap(iter, actors.end() - 1);
			actors.pop_back();
		}
	}

	auto aActors = mActors.find(type);
	if (aActors != mActors.end())
	{
		auto& actors = aActors->second;
		auto iter = std::find_if(actors.begin(), actors.end(),
			[&actor](const std::weak_ptr<Actor>& act)
			{return actor.lock() == act.lock(); });
		if (iter != actors.end())
		{
			std::iter_swap(iter, actors.end() - 1);
			actors.pop_back();
		}
	}
}

void Scene::addUI(const std::shared_ptr<class UI>& ui)
{
	mUserInterfaces.emplace_back(ui);
}

void Scene::pauseAllActor()
{
	for (const auto& actors : mActors)
	{
		for (const auto& actor : actors.second)
		{
			actor->setState(Actor::State::Paused);
		}
	}

	for (const auto& actors : mReadyActors)
	{
		for (const auto& actor : actors.second)
		{
			actor->setState(Actor::State::Paused);
		}
	}
}

void Scene::activeAllActor()
{
	for (const auto& actors : mActors)
	{
		for (const auto& actor : actors.second)
		{
			actor->setState(Actor::State::Active);
		}
	}

	for (const auto& actors : mReadyActors)
	{
		for (const auto& actor : actors.second)
		{
			actor->setState(Actor::State::Active);
		}
	}
}

const std::vector<std::shared_ptr<class Actor>> Scene::getActors(std::string type) const
{
	auto actors = mActors.find(type);
	if (actors != mActors.end())
	{
		return actors->second;
	}
	std::vector<std::shared_ptr<class Actor>> ret;
	return ret;
}