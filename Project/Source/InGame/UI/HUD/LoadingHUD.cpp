#include "LoadingHUD.h"
#include "../../Scene/LoadingScene.h"
#include "../../Map/GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Graphics/Renderer/Renderer.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../../Game/Graphics/Texture/Texture.h"

LoadingHUD::LoadingHUD(const std::weak_ptr<class LoadingScene>& scene, const std::weak_ptr<class Renderer>& render)
	: HUD(scene, render)
	, mLoadingScene(scene)
	, mFPS(31)
	, mfidx(0)
	, mtime(0.0)
{

}

LoadingHUD::~LoadingHUD()
{

}

void LoadingHUD::initailize()
{
	HUD::initailize();
	
	for (int i = 0; i < mFPS; ++i)
	{
		std::string filename = "Asset/Image/LoadingScene/frame-" + std::to_string(i) + ".png";
		mLoadimage = mRenderer.lock()->getTexture(filename);
	}




}

void LoadingHUD::resetInfo()
{
}

void LoadingHUD::update(float deltatime)
{
	mtime += deltatime;
	mfidx = std::round(mtime * mFPS);
	std::string filename = "Asset/Image/LoadingScene/frame-" + std::to_string(mfidx % mFPS) + ".png";
	mLoadimage = mRenderer.lock()->getTexture(filename);
	mtime = std::fmodf(mtime, 1.0);	//if문으로 반복해주는거말고 나머지연산으로 if문 대체
}

void LoadingHUD::processInput()
{

}

void LoadingHUD::draw(std::unique_ptr<class Shader>& shader)
{
	auto wSize = mRenderer.lock()->getWindow()->getSize();
	drawTexture(shader, mLoadimage, Vector2(0.0f, 20.0f));
}