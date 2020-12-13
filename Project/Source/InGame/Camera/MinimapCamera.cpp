#include "MinimapCamera.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Actor/Actor.h"


GameMinimap::GameMinimap(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, const std::weak_ptr<class Actor>& owner, bool standard)
	: Minimap(scene, render, owner, standard)
{
}

GameMinimap::~GameMinimap()
{

}

void GameMinimap::initailize()
{
	Minimap::initailize();
}

void GameMinimap::update(float deltatime)
{
	Minimap::update(deltatime);
}

void GameMinimap::draw(std::unique_ptr<Shader>& shader)
{
	if (mTexture)
	{
		auto pos = mOwner.lock()->getPosition();
		auto standardpos = mStandard.lock()->getPosition();
		auto calpos = pos - standardpos;
		//Vector2 WorldToMini(pos.z * -1 / mMapSize.x * mMinimapSize.x, pos.x / mMapSize.y * mMinimapSize.y);
		Vector2 WorldToMini(calpos.z * -1, calpos.x);
		Vector2 World(mOwner.lock()->getPosition().x, mOwner.lock()->getPosition().z);
		auto wSize = mRenderer.lock()->getWindow()->getSize();
		//drawTexture(shader, mTexture, Vector2(WorldToMini.x, WorldToMini.y));
		drawTexture(shader, WorldToMini);
	}
}
