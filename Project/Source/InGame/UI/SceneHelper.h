#pragma once
#include <memory>
#include <string>
#include "../Info/GameInfo.h"

class SceneHelper
{
public:
	SceneHelper(const std::weak_ptr<class Scene>& scene);
	~SceneHelper() noexcept;

	void changeToTitleScene(const GameInfo& info);
	void changeToGameScene(const GameInfo& info, int stage);
	void changeToEditScene(const GameInfo& info);
	void changeToShopScene(const GameInfo& info);
	void changeToSettingScene(const GameInfo& info);
	void quitGame();
	void createDialog(const std::string& typeName);

private:
	std::weak_ptr<class Scene> mScene;
};