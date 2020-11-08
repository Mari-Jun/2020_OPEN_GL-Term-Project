#include "RobotArm.h"
#include "../../Graphics/Window.h"
#include "../../Game.h"
#include "../../Component/MoveComponent.h"
#include "../../Component/BoxComponent.h"
#include "../../Graphics/Mesh/MeshComponent.h"
#include "../../Input/KeyBoard.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../PlaneActor.h"

RobotArm::RobotArm(const std::weak_ptr<class Game>& game, bool front)
	: Actor(game)
	, mFront(front)
	, mMove(false)
	, mRot(0.0f)
{
	
}

RobotArm::~RobotArm()
{

}

void RobotArm::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Box.obj");
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->initailize();
	mMeshComponent->setMesh(mesh);
	mMeshComponent->setColor(mMeshColor);
}

void RobotArm::updateActor(float deltatime)
{
	if (mRot >= 90.0f)
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
		if(Math::Abs(mRot) >= 1.0f)
			mRot += rotSpeed * deltatime;
	}
	
	setPosition(getPosition() - getUp() * getScale().y / 2);

	mMove = false;
}

void RobotArm::actorInput()
{

}