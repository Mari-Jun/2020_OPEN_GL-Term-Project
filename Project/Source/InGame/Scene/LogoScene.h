#pragma once
#include "../../Game/Scene/Scene.h"

class LogoScene : public Scene
{
public:
	LogoScene(const std::weak_ptr<class Game>& game);
	virtual ~LogoScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();

private:
	int count;

};
