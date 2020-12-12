#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	enum class SceneState
	{
		Active,
		Paused,
		Dead
	};

	Scene(const std::weak_ptr<class Game>& game);
	virtual ~Scene() noexcept;

	virtual void initailize();

	void processInput();
	virtual void sceneInput();
	void uiInput();

	void update();
	virtual void sceneUpdate(float deltatime);
	void uiUpdate(float deltatime);

	virtual void draw();

	virtual void loadData();
	virtual void unLoadData();
	
	void addActor(const std::string& type, const std::shared_ptr<class Actor>& actor);
	void removeActor(const std::string& type, const std::weak_ptr<class Actor>& actor);
	void addUI(const std::shared_ptr<class UI>& ui);

	void pauseAllActor();
	void activeAllActor();

private:
	SceneState mState;
	std::weak_ptr<class Game> mGame;

	std::unordered_map<std::string, std::vector<std::shared_ptr<class Actor>>> mActors;
	std::unordered_map<std::string, std::vector<std::shared_ptr<class Actor>>> mReadyActors;
	std::vector<std::shared_ptr<class UI>> mUserInterfaces;

	bool mIsUpdateActor;

public:
	SceneState getSceneState() const { return mState; }
	void setSceneState(SceneState state) { mState = state; }
	const std::weak_ptr<class Game>& getGame() const { return mGame; }
	std::weak_ptr<class Game>& getGame() { return const_cast<std::weak_ptr<class Game>&>(std::as_const(*this).getGame()); }
	const std::vector<std::shared_ptr<class Actor>> getActors(std::string type) const;
	const std::vector<std::shared_ptr<class UI>>& getUserInterfaces() const { return mUserInterfaces; }
};
