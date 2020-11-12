#include "RobotArm.h"
#include "../../Graphics/Window.h"
#include "../../Game.h"
#include "../../Component/MoveComponent.h"
#include "../../Component/BoxComponent.h"
#include "../../Graphics/Mesh/MeshComponent.h"
#include "../../Input/KeyBoard.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../PlaneActor.h"

RobotArm::RobotArm(const std::weak_ptr<class Game>& game, bool left)
	: Actor(game, Type::Player)
	, mLeft(left)
	, mRot(0.0f)
	, mRotSpeed(mLeft ? 300.0f : -300.0f)
{
	
}

RobotArm::~RobotArm()
{

}

void RobotArm::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	std::string arm = mLeft ? "PlayerLArm" : "PlayerRArm";
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Player/" + arm);
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setTexture("Asset/Mesh/Player/skin_man.png");
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();
}

void RobotArm::updateActor(float deltatime)
{
	if (mRot >= 60.0f && mRotSpeed > 0.0f ||
		mRot <= -60.0f && mRotSpeed < 0.0f)
	{
		mRotSpeed *= -1;
	}

	setPosition(getPosition() + getUp() * getScale().y * 11);

	Quaternion q = getRotation();
	q = Quaternion::Concatenate(q, Quaternion(getSide(), Math::ToRadians(mRot)));
	setRotation(q);

	if (mMove)
	{
		mRot += mRotSpeed * deltatime;
	}
	else
	{
		if (Math::Abs(mRot) >= 2.0f)
		{
			mRot += mRotSpeed * deltatime;
		}
		else
		{
			mRot = 0.0f;
		}
	}
	
	setPosition(getPosition() - getUp() * getScale().y * 11);

	mMove = false;
}

void RobotArm::actorInput()
{

}