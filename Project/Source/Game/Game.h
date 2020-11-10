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

	//std::stack<std::unique_ptr<class Scene>> mScene;

	std::vector<std::shared_ptr<class Actor>> mActor;
	std::vector<std::shared_ptr<class Actor>> mReadyActor;

	bool mIsUpdateActor;

	std::shared_ptr<class CameraActor> mMouseCamera;
	std::shared_ptr<class FollowCameraActor> mFollowCamera;
	std::vector<std::shared_ptr<class PlaneActor>> mPlaneActor;

public:
	void run();
	void shutDown();

	const std::shared_ptr<class Renderer>& getRenderer() const { return mRenderer; }
	const std::shared_ptr<class PhysEngine>& getPhysEngine() const { return mPhysEngine; }
	const std::unique_ptr<class KeyBoard>& getKeyBoard() const { return mKeyBoard; }
	const std::unique_ptr<class Mouse>& getMouse() const { return mMouse; }

	void addActor(const std::shared_ptr<class Actor>& actor);
	void removeActor(const std::weak_ptr<class Actor>& actor);
	void addPlane(const std::shared_ptr<class PlaneActor>& plane);
	void removePlane(const std::weak_ptr<class PlaneActor>& plane);

	const std::vector<std::shared_ptr<class PlaneActor>>& getPlanes() { return mPlaneActor; }

private:
	void processInput();
	void update();
	void draw();
	
	void loadData();
	void unLoadData();
	void loadActorData();
	void loadWorldBox();
};