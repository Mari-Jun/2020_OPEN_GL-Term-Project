#include "LightTile.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Game.h"
#include "../../../Game/Graphics/Light/Light.h"

LightTile::LightTile(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Light>& light, const std::string& time)
	: Tile(scene, TileType::Light)
	, mLight(light)
	, mTime(time)
{

}

LightTile::~LightTile()
{
	if (mTime != "Sunny")
	{
		turnOffLight();
	}

	mLightActor->setState(State::Dead);
}

void LightTile::initailize()
{
	Tile::initailize();

	mLightActor = std::make_shared<Actor>(getScene());
	mLightActor->setScale(getScale() * 0.5f);
	mLightActor->setRotation(getRotation());
	mLightActor->setPosition(getPosition() + getUp() * getScale().y * 0.1f + getSide() * getScale().x * 0.4f);
	mLightActor->initailize();

	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Tile/Road/Tile_Light");
	auto meshComp = std::make_shared<MeshComponent>(mLightActor, getGame().lock()->getRenderer());
	meshComp->setMesh(mesh);
	meshComp->initailize();
	auto box = std::make_shared<BoxComponent>(mLightActor, getGame().lock()->getPhysEngine());
	box->setObjectBox(mesh->getBox());
	box->initailize();

	if (mTime != "Sunny")
	{
		turnOnLight();
	}
}

void LightTile::updateActor(float deltatime)
{
	mLightActor->setRotation(getRotation());
	mLightActor->setPosition(getPosition() + getUp() * getScale().y * 0.1f + getSide() * getScale().x * 0.4f);
}

void LightTile::turnOnLight()
{
	PointLight pLight;
	pLight.position = mLightActor->getPosition() + getUp() * getScale().x * 0.6f;
	pLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	pLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
	pLight.constant = 1.0f;
	pLight.linear = 0.035f;
	pLight.quadratic = 0.000068f;

	mPointLight = std::make_shared<PointLight>(pLight);

	mLight.lock()->addPointLight(mPointLight);
}

void LightTile::turnOffLight()
{
	mLight.lock()->removePointLight(mPointLight);
}