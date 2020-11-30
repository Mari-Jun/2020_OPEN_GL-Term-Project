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


}

void CubeMap::updateActor(float deltatime)
{
}

void CubeMap::actorInput()
{

}


