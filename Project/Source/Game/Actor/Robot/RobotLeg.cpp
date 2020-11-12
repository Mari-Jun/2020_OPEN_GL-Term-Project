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
	mMeshComponent->initailize();
	mMeshComponent->setMesh(mesh);
}

void RobotLeg::updateActor(float deltatime)
{
	/*if (mRot >= 90.0f)
	{
		mFront = false;
	}
	if (mRot <= -90.0f)
	{
		mFront = true;
	}

	float rotSpeed = 400.0f;
	if (!mFront)
		rotSpeed *= -1;

	setPosition(getPosition() + getUp() * getScale().y / 2);

	Quaternion q = getRotation();
	q = Quaternion::Concatenate(q, Quaternion(getSide(), Math::ToRadians(mRot)));
	setRotation(q);

	if (mMove)
	{
		mRot += rotSpeed * deltatime;
	}
	else
	{
		if (Math::Abs(mRot) >= 1.0f)
			mRot += rotSpeed * deltatime;
	}

	setPosition(getPosition() - getUp() * getScale().y / 2);

	mMove = false;*/
}

void RobotLeg::actorInput()
{

}