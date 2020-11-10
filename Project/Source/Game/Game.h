#pragma once
#include <gl/freeglut.h>
#include <unordered_map>
#include <iostream>
#include <stack>

class Game final : public std::enable_shared_from_this<Game>
{
public:
	Game();
	~Game() noexcept;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool initialize(int argc, char** argv);
private:
	std::shared_ptr<class Renderer> mRenderer;
	std::shared_ptr<class PhysEngine> mPhysEngine;
	std::unique_ptr<class DeltaTime> mDeltaTime;
	std::unique_ptr<class KeyBoard> mKeyBoard;
	std::unique_ptr<class Mouse> mMouse;

	bool mIsRunning;
	bool mIsPaused;

	std::string nName;

	std::stack<std::unique_ptr<class Scene>> mScene;

	bool mIsUpdateActor;

public:
	void run();
	void shutDown();

	const std::shared_ptr<class Renderer>& getRenderer() const { return mRenderer; }
	const std::shared_ptr<class PhysEngine>& getPhysEngine() const { return mPhysEngine; }
	const std::unique_ptr<class KeyBoard>& getKeyBoard() const { return mKeyBoard; }
	const std::unique_ptr<class Mouse>& getMouse() const { return mMouse; }

	void revertScene(std::unique_ptr<class Scene>&& scene);
	void clearScene();
	void pushScene(std::unique_ptr<class Scene>&& scene);
	void popScene();

	void addActor(const std::shared_ptr<class Actor>& actor);
	void removeActor(const std::weak_ptr<class Actor>& actor);

private:
	void processInput();
	void update();
	void draw();
	
	void loadData();
	void unLoadData();
};