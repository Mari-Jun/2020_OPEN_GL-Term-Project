#pragma once
#include "HUD.h"

class SettingHUD : public HUD
{
public:

	SettingHUD(const std::weak_ptr<class SettingScene>& scene, const std::weak_ptr<class Renderer>& render);
	~SettingHUD();

	virtual void initailize();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

private:
	std::weak_ptr<class SettingScene> mSettingScene;
	std::shared_ptr<class Texture> mBGMstate;
	std::shared_ptr<class Texture> mEFFECTstate;

private:
	int BGMVolume;
	int EFFECTVolume;

};