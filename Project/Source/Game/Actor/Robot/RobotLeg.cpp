#include "RobotLeg.h"
#include "../../Graphics/Window.h"
#include "../../Game.h"
#include "../../Component/MoveComponent.h"
#include "../../Component/BoxComponent.h"
#include "../../Graphics/Mesh/MeshComponent.h"
#include "../../Input/KeyBoard.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../PlaneActor.h"

RobotLeg::RobotLeg(const std::weak_ptr<class Game>& game, bool left)
	: Actor(game, Type::Player)
	, mLeft(left)
	, mMove(false)
	, mRot(0.0f)
	, mRotSpeed(mLeft ? -300.0f : 300.0f)
{

}

RobotLeg::~RobotLeg()
{

}

void RobotLeg::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	std::string leg = mLeft ? "PlayerLLeg" : "PlayerRLeg";
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Player/" + leg);
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setTexture("Asset/Mesh/Player/skin_man.png");
	mMeshComponent->setMesh(mesh);
	mMeshComponent->initailize();
}

void RobotLeg::updateActor(float deltatime)
{
	if (mRot >= 60.0f && mRotSpeed > 0.0f ||
		mRot <= -60.0f && mRotSpeed < 0.0f)
	{
		mRotSpeed *= -1;
	}

	setPosition(getPosition() + getUp() * getScale().y * 5);

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

	setPosition(getPosition() - getUp() * getScale().y * 5);

	mMove = false;
}

void RobotLeg::actorInput()
{

}