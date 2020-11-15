#include "RobotActor.h"
#include "RobotHead.h"
#include "RobotArm.h"
#include "RobotLeg.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Game.h"
#include "../../../Game/Component/MoveComponent.h"
#include "../../../Game/Component/BoxComponent.h"
#include "../../../Game/Graphics/Mesh/MeshComponent.h"
#include "../../../Game/Input/KeyBoard.h"
#include "../../../Game/Graphics/Mesh/Mesh.h"
#include "../../../Game/Actor/PlaneActor.h"

RobotActor::RobotActor(const std::weak_ptr<class Game>& game)
	: Actor(game, Type::Player)
	, mGravitySpeed(0.0f)
	, mAnimation(false)
{

}

RobotActor::~RobotActor()
{
	
}

void RobotActor::initailize()
{
	Actor::initailize();

	//Create MeshComponent
	auto mesh = getGame().lock()->getRenderer()->getMesh("Asset/Mesh/Player/PlayerBody");
	mMeshComponent = std::make_shared<MeshComponent>(weak_from_this(), getGame().lock()->getRenderer());
	mMeshComponent->setMesh(mesh);
	mMeshComponent->setTexture("Asset/Mesh/Player/skin_man.png");
	mMeshComponent->initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), getGame().lock()->getPhysEngine());
	mBoxComponent->setObjectBox(mesh->getBox());
	mBoxComponent->initailize();

	//Create Head
	mHead = std::make_shared<RobotHead>(getGame());
	mHead->setScale(getScale());
	mHead->initailize();

	//Create Arm
	mLeftArm = std::make_shared<RobotArm>(getGame(), true);
	mLeftArm->setScale(getScale());
	mLeftArm->initailize();

	mRightArm = std::make_shared<RobotArm>(getGame(), false);
	mRightArm->setScale(getScale());
	mRightArm->initailize();

	//Create Leg
	mLeftLeg = std::make_shared<RobotLeg>(getGame(), false);
	mLeftLeg->setScale(getScale());
	//이런 느낌
	auto leftLegPos = -1 * getUp() * (mLeftLeg->getScale().y + getScale().y) / 2 - getSide() * mLeftLeg->getScale().x;
	mBoxComponent->updateObjectBox(leftLegPos + mLeftLeg->getScale() / 2);
	mBoxComponent->updateObjectBox(leftLegPos - mLeftLeg->getScale() / 2);
	mLeftLeg->initailize();

	mRightLeg = std::make_shared<RobotLeg>(getGame(), true);
	mRightLeg->setScale(getScale());
	mRightLeg->initailize();
}

void RobotActor::updateActor(float deltatime)
{
	//중력 설정
	if (mGravitySpeed > -10000.0f)
		mGravitySpeed -= 100.0f;

	mMoveComponent->setUpSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getUp()));
	mMoveComponent->setForwardSpeed( mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getForward()));
	mMoveComponent->setSideSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getSide()));

	collides(mBoxComponent);

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

void RobotActor::actorInput()
{
	auto game = getGame().lock();

	float forwardSpeed = 0.0f;

	if (game->getKeyBoard()->isKeyPressed('w') ||
		game->getKeyBoard()->isKeyPressed('a') ||
		game->getKeyBoard()->isKeyPressed('s') ||
		game->getKeyBoard()->isKeyPressed('d'))
	{
		forwardSpeed = 100.0f;
		mLeftArm->setMove(true);
		mRightArm->setMove(true);
		mLeftLeg->setMove(true);
		mRightLeg->setMove(true);
	}

	if (game->getKeyBoard()->isKeyPressed(32))
	{
		mGravitySpeed = 2000.0f;
	}

	mMoveComponent->setForwardSpeed(forwardSpeed);
}

void RobotActor::collides(const std::weak_ptr<BoxComponent>& bComp)
{
	updateWorldTransform();

	AABB robotBox = bComp.lock()->getWorldBox();
	
	Vector3 pos = getPosition();

	auto allBoxes = getGame().lock()->getPhysEngine()->getBoxes();
	auto boxes = allBoxes.find(getTypeToString(Type::Object));
	if (boxes != allBoxes.end())
	{
		for (auto b : boxes->second)
		{
			const AABB& box = b.lock()->getWorldBox();
			const auto& boxActor = b.lock()->getOwner();

			if (shared_from_this() != boxActor.lock() && Intersect(robotBox, box))
			{
				float dx1 = box.mMax.x - robotBox.mMin.x;
				float dx2 = box.mMin.x - robotBox.mMax.x;
				float dy1 = box.mMax.y - robotBox.mMin.y;
				float dy2 = box.mMin.y - robotBox.mMax.y;
				float dz1 = box.mMax.z - robotBox.mMin.z;
				float dz2 = box.mMin.z - robotBox.mMax.z;

				float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
				float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
				float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

				if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
				{
					pos.x += dx;
				}
				if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
				{
					pos.y += dy;
					mGravitySpeed = 0.0f;
				}
				if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
				{
					pos.z += dz;
				}

				setPosition(pos);
				mBoxComponent->updateWorldTransForm();
			}
		}
	}
}