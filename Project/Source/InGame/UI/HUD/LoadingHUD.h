#pragma once
#include "HUD.h"

using vTexSet = std::vector<std::shared_ptr<class Texture>>;

class LoadingHUD : public HUD
{
public:
	LoadingHUD(const std::weak_ptr<class LoadingScene>& scene, const std::weak_ptr<class Renderer>& render);
	~LoadingHUD();

	virtual void initailize();
	virtual void resetInfo();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);


private:
	std::weak_ptr<class LoadingScene> mLoadingScene;
	std::shared_ptr<class Texture> mLoadimage;
	int mFPS;
	int mfidx;
	float mtime;

};