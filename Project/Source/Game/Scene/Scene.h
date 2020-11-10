#pragma once
#include <vector>
#include <memory>

class Scene
{
public:
	Scene(const std::weak_ptr<class Game>& game);
	virtual ~Scene();

	void processInput();
	void update();
	void draw();

	void addActor(const std::shared_ptr<class Actor>& actor);
	void removeActor(const std::weak_ptr<class Actor>& actor);

private:
	std::weak_ptr<class Game> mGame;

	std::vector<std::shared_ptr<class Actor>> mActor;
	std::vector<std::shared_ptr<class Actor>> mReadyActor;

	bool mIsUpdateActor;
};
