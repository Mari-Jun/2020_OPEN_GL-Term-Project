#include "LightTile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"
#include "../../../Game/Graphics/Light/Light.h"

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
	mLight->setScale(getScale() * 0.5f);
	mLight->setRotation(getRotation());
	mLight->setPosition(getPosition() + getUp() * getScale().y * 0.1f + getSide() * getScale().x * 0.4f);
	mLight->initailize();

	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Tile/Road/Tile_Light");
	auto meshComp = std::make_shared<MeshComponent>(mLight, getGame().lock()->getRenderer());
	meshComp->setMesh(mesh);
	meshComp->initailize();
	auto box = std::make_shared<BoxComponent>(mLight, getGame().lock()->getPhysEngine());
	box->setObjectBox(mesh->getBox());
	box->initailize();

	turnOnLight();
}

void LightTile::updateActor(float deltatime)
{
	mLight->setRotation(getRotation());
	mLight->setPosition(getPosition() + getUp() * getScale().y * 0.1f + getSide() * getScale().x * 0.4f);
}

void LightTile::turnOnLight()
{
	const auto& light = getGame().lock()->getRenderer()->getLight();

	PointLight pLight;
	pLight.position = mLight->getPosition() + getUp() * getScale().x * 0.5f;
	pLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	pLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	pLight.constant = 1.0f;
	pLight.linear = 0.0035;
	pLight.quadratic = 0.000055f;

	light->addPointLight(std::make_shared<PointLight>(pLight));
}

void LightTile::turnOffLight()
{

}