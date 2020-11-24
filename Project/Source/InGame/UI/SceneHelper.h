#pragma once
#include <memory>
#include <string>
#include "../Info/GameInfo.h"

class SceneHelper
{
public:
	SceneHelper(const std::weak_ptr<class Scene>& scene);
	~SceneHelper() noexcept;

	void changeToTitleScene(GameInfo info);
	void changeToGameScene(GameInfo info);
	void changeToEditScene(GameInfo info);
	void quitGame();
	void createDialog(const std::string& typeName);

private:
	std::weak_ptr<class Scene> mScene;
};