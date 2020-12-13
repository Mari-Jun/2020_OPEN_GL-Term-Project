#include "SettingHUD.h"
#include "../../Scene/SettingScene.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Sound/Sound.h"
#include "../../../Game/Graphics/Texture/Texture.h"


SettingHUD::SettingHUD(const std::weak_ptr<class SettingScene>& scene, const std::weak_ptr<class Renderer>& render)
	: HUD(scene, render)
	, mSettingScene(scene)
{

}

SettingHUD::~SettingHUD()
{

}

void SettingHUD::initailize()
{
	HUD::initailize();
	mBGMstate = mRenderer.lock()->getTexture("Asset/Image/Setting/" + std::to_string(int(mSettingScene.lock()->getGame().lock()->getSound()->getBGMVolume() * 10)) + ".png");
	mEFFECTstate = mRenderer.lock()->getTexture("Asset/Image/Setting/" + std::to_string(int(mSettingScene.lock()->getGame().lock()->getSound()->getEFFECTVolume() * 10)) + ".png");
}

void SettingHUD::update(float deltatime)
{

}

void SettingHUD::processInput()
{

}

void SettingHUD::draw(std::unique_ptr<class Shader>& shader)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();

	std::cout << int( mSettingScene.lock()->getGame().lock()->getSound()->getBGMVolume()*10) << std::endl;
	mBGMstate = mRenderer.lock()->getTexture("Asset/Image/Setting/" + std::to_string(int(std::round(mSettingScene.lock()->getGame().lock()->getSound()->getBGMVolume() * 10))) + ".png");
	mEFFECTstate = mRenderer.lock()->getTexture("Asset/Image/Setting/" + std::to_string(int(std::round(mSettingScene.lock()->getGame().lock()->getSound()->getEFFECTVolume() * 10))) + ".png");
	drawTexture(shader, mBGMstate, Vector2(0.0f, 50.0f));
	drawTexture(shader, mEFFECTstate, Vector2(0.0f, -200.0f));
	
}