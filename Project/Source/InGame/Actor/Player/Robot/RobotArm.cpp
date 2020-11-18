#include "RobotArm.h"
#include "../../../../Game/Component/BoxComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Game.h"

RobotArm::RobotArm(const std::weak_ptr<class Scene>& scene, bool left)
	: Actor(scene, Type::Etc)
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