#pragma once
#include "../../Info/GameInfo.h"
#include "HUD.h"

using vTexSet = std::vector<std::shared_ptr<class Texture>>;

class StageHUD : public HUD
{
public:
	StageHUD(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, const GameInfo& info);
	~StageHUD();

	virtual void initailize();
	virtual void resetInfo();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

	void back();
	void next();
	void play();

private:
	GameInfo mInfo;
	int mStage;
	std::vector<std::shared_ptr<class Texture>> mStageCount;

public:
	int getStage() const { return mStage; }
};