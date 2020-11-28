#include "RobotLeg.h"
#include "../../../../Game/Component/BoxComponent.h"
#include "../../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../../Game/Game.h"

RobotLeg::RobotLeg(const std::weak_ptr<class Scene>& scene, bool left)
	: Actor(scene, Type::Etc)
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

void RobotLeg::setPlayerTexture(const std::string& fileName, int index)
{
	mMeshComponent->setTexture(fileName);
	mMeshComponent->setTextureIndex(index);
}

void RobotLeg::resetTexture()
{
	mMeshComponent->resetTexture();
}