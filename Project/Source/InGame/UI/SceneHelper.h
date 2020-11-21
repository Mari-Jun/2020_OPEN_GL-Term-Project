#pragma once
#include <memory>

class SceneHelper
{
public:
	SceneHelper(const std::weak_ptr<class Scene>& scene);
	~SceneHelper() noexcept;

	void changeToTitleScene();
	void changeToGameScene();
	void changeToEditScene();
	void quitGame();
	void notYet();

private:
	std::weak_ptr<class Scene> mScene;
};