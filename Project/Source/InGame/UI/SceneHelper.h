#pragma once
#include <memory>
#include <string>

class SceneHelper
{
public:
	SceneHelper(const std::weak_ptr<class Scene>& scene);
	~SceneHelper() noexcept;

	void changeToTitleScene();
	void changeToGameScene();
	void changeToEditScene();
	void quitGame();
	void createDialog(const std::string& typeName);

private:
	std::weak_ptr<class Scene> mScene;
};