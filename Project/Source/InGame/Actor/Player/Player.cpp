#include "Player.h"
#include "Robot/RobotHead.h"
#include "Robot/RobotArm.h"
#include "Robot/RobotLeg.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Game.h"
#include "../../../Game/Component/MoveComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Graphics/Mesh/BillBoardComponent.h"	
#include "../../../Game/Input/KeyBoard.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"

Player::Player(const std::weak_ptr<class Scene>& scene, PlayerInfo info)
	: Actor(scene, Type::Player)
	, mPlayerInfo(info)
{

}

Player::~Player()
{

}

void Player::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Player/PlayerBody");
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();

	//Create Head
	mHead = std::make_shared<RobotHead>(getScene());
	mHead->setScale(getScale());
	mHead->initailize();

	//Create Arm
	mLeftArm = std::make_shared<RobotArm>(getScene(), true);
	mLeftArm->setScale(getScale());
	mLeftArm->initailize();

	mRightArm = std::make_shared<RobotArm>(getScene(), false);
	mRightArm->setScale(getScale());
	mRightArm->initailize();

	//Create Leg
	mLeftLeg = std::make_shared<RobotLeg>(getScene(), false);
	mLeftLeg->setScale(getScale());
	mLeftLeg->initailize();

	mRightLeg = std::make_shared<RobotLeg>(getScene(), true);
	mRightLeg->setScale(getScale());
	mRightLeg->initailize();

	setPlayerTexture();
}

void Player::updateActor(float deltatime)
{
	updateBody();
}

void Player::actorInput()
{
	
}

void Player::updateBody()
{
	mHead->setRotation(getRotation());
	mHead->setPosition(getPosition());

	mLeftArm->setRotation(getRotation());
	mLeftArm->setPosition(getPosition());

	mRightArm->setRotation(getRotation());
	mRightArm->setPosition(getPosition());

	mLeftLeg->setPosition(getPosition());
	mLeftLeg->setRotation(getRotation());

	mRightLeg->setPosition(getPosition());
	mRightLeg->setRotation(getRotation());
}

void Player::setPlayerTexture()
{
	auto fileName = mPlayerInfo.getSkinFileName();
	auto index = static_cast<int>(mPlayerInfo.mSkinType);
	mMeshComponent->setTexture(fileName);
	mMeshComponent->setTextureIndex(index);
	mLeftArm->setPlayerTexture(fileName, index);
	mRightArm->setPlayerTexture(fileName, index);
	mLeftLeg->setPlayerTexture(fileName, index);
	mRightLeg->setPlayerTexture(fileName, index);
	mHead->setPlayerTexture(fileName, index);
}