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
	std::unique_ptr<class KeyBoard> mKeyBoard;
	std::unique_ptr<class Mouse> mMouse;
	std::shared_ptr<class Sound> mSound;

	bool mIsRunning;
	bool mIsPaused;

	std::string nName;

	std::vector<std::shared_ptr<class Scene>> mScene;
	std::vector<std::shared_ptr<class Scene>> mReadyScene;

	bool mIsUpdateScene;

public:
	void run();
	void shutDown();

	const std::shared_ptr<class Renderer>& getRenderer() const { return mRenderer; }
	const std::shared_ptr<class PhysEngine>& getPhysEngine() const { return mPhysEngine; }
	const std::unique_ptr<class KeyBoard>& getKeyBoard() const { return mKeyBoard; }
	const std::unique_ptr<class Mouse>& getMouse() const { return mMouse; }
	const std::shared_ptr<class Sound>& getSound() const { return mSound; }

	void revertScene(const std::shared_ptr<class Scene>& scene);
	void clearScene();
	void addScene(const std::shared_ptr<class Scene>& scene);
	void removeScene(const std::weak_ptr<class Scene>& scene);

private:
	void processInput();
	void update();
	void draw();
	
	void loadData();
	void unLoadData();
};