#include "LightTile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"
#include "../../Actor/Enemy/EnemyTower.h"

LightTile::LightTile(const std::weak_ptr<class Scene>& scene, Type type)
	: Tile(scene, type)
{

}

LightTile::~LightTile()
{
	mLight->setState(State::Dead);
}

void LightTile::initailize()
{
	Tile::initailize();

	mLight = std::make_shared<Actor>(getScene());
	mLight->setScale(getScale());
	mLight->setRotation(getRotation());
	mLight->setPosition(getPosition());
	mLight->initailize();

	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Tile/Road/Tile_Light");
	auto meshComp = std::make_shared<MeshComponent>(mLight, getGame().lock()->getRenderer());
	meshComp->setMesh(mesh);
	meshComp->initailize();
	auto box = std::make_shared<BoxComponent>(mLight, getGame().lock()->getPhysEngine());
	box->setObjectBox(mesh->getBox());
	box->initailize();
	
}

void LightTile::updateActor(float deltatime)
{
	mLight->setRotation(getRotation());
	mLight->setPosition(getPosition() + getUp() * getScale().y * 0.1f + getSide() * getScale().x * 0.4f);
}