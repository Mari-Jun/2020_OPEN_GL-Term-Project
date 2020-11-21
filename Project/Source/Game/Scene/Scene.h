#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	enum class State
	{
		Active,
		Paused,
		Dead
	};

	Scene(const std::weak_ptr<class Game>& game);
	virtual ~Scene() noexcept;

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);
	void draw();

	virtual void loadData();
	virtual void unLoadData();
	
	void addActor(const std::string& type, const std::shared_ptr<class Actor>& actor);
	void removeActor(const std::string& type, const std::weak_ptr<class Actor>& actor);
	void addUI(const std::shared_ptr<class UI>& ui);

private:
	State mState;
	std::weak_ptr<class Game> mGame;

	std::unordered_map<std::string, std::vector<std::shared_ptr<class Actor>>> mActors;
	std::unordered_map<std::string, std::vector<std::shared_ptr<class Actor>>> mReadyActors;
	std::vector<std::shared_ptr<class UI>> mUserInterfaces;

	bool mIsUpdateActor;

public:
	State getState() const { return mState; }
	void setState(State state) { mState = state; }
	const std::weak_ptr<class Game>& getGame() const { return mGame; }
	std::weak_ptr<class Game>& getGame() { return const_cast<std::weak_ptr<class Game>&>(std::as_const(*this).getGame()); }
	const std::vector<std::shared_ptr<class Actor>>& getActors(std::string type) const;
	const std::vector<std::shared_ptr<class UI>>& getUserInterfaces() const { return mUserInterfaces; }

protected:

};
