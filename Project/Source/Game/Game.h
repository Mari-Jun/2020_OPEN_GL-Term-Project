#pragma once
#include <gl/freeglut.h>
#include <unordered_map>
#include <iostream>
#include <queue>

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

	std::vector<std::shared_ptr<class Actor>> mActor;
	std::vector<std::shared_ptr<class Actor>> mReadyActor;

	bool mIsUpdateActor;

	std::shared_ptr<class CameraActor> mCameraActor;
	std::vector<std::shared_ptr<class PlaneActor>> mPlaneActor;

	std::shared_ptr<class DefualtShape> mLightActor;
	bool mLightAni;

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

	bool getLightAni() const { return mLightAni; }

private:
	void processInput();
	void update();
	void draw();
	
	void loadData();
	void unLoadData();
};