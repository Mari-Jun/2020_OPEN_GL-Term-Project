#include "CubeMap.h"

#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Game.h"	
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/CubeMapComponent.h"

CubeMap::CubeMap(const std::weak_ptr<class Scene>& scene)
	: Actor(scene)
{
}

CubeMap::~CubeMap()
{
}

void CubeMap::initailize()
{
	Actor::initailize();

	std::vector<std::string> face{
		"Asset/Image/SkyBox/right.jpg",
		"Asset/Image/SkyBox/left.jpg",
		"Asset/Image/SkyBox/top.jpg",
		"Asset/Image/SkyBox/bottom.jpg",
		"Asset/Image/SkyBox/front.jpg",
		"Asset/Image/SkyBox/back.jpg",

	};
	//Create CubeMap
	mCubeMap = std::make_shared<CubeMapComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mCubeMap->initailize();
	mCubeMap->setTexture(face);
}

void CubeMap::updateActor(float deltatime)
{
}

void CubeMap::actorInput()
{

}


