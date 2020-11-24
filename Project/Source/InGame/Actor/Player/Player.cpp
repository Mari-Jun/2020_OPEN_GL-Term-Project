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

Player::Player(const std::weak_ptr<class Scene>& scene, PlayerType type)
	: Actor(scene, Type::Player)
	, mStat({})
	, mType(type)
	, mGravitySpeed(0.0f)
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

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), getGame().lock()->getPhysEngine());
	mBoxComponent->setObjectBox(mesh->getBox());
	mBoxComponent->initailize();

	//Create HealthBar
	mHealthBar = std::make_shared<Actor>(getScene(), Type::Ui);
	auto hp = std::make_shared<BillBoardComponent>(mHealthBar, getGame().lock()->getRenderer());
	hp->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/Player/RedBar.png"));
	hp->initailize();
	mHealthBar->setScale(0.1f);
	mHealthBar->setPosition(getPosition() + Vector3::UnitY * 30.0f);
	mHealthBar->initailize();

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
	//�̷� ����
	auto leftLegPos = -1 * getUp() * (mLeftLeg->getScale().y + getScale().y) / 2 - getSide() * mLeftLeg->getScale().x;
	mBoxComponent->updateObjectBox(leftLegPos + mLeftLeg->getScale() / 2);
	mBoxComponent->updateObjectBox(leftLegPos - mLeftLeg->getScale() / 2);
	mLeftLeg->initailize();

	mRightLeg = std::make_shared<RobotLeg>(getScene(), true);
	mRightLeg->setScale(getScale());
	mRightLeg->initailize();
}

void Player::updateActor(float deltatime)
{
	updateGravity(deltatime);

	collides(mBoxComponent);

	mHealthBar->setPosition(getPosition() + Vector3::UnitY * 30.0f);

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

	if (mStat.mSpeed != 0.0f)
	{
		mLeftArm->setMove(true);
		mRightArm->setMove(true);
		mLeftLeg->setMove(true);
		mRightLeg->setMove(true);
	}
}

void Player::actorInput()
{
	
}

void Player::updateGravity(float deltatime)
{
	//�߷� ����
	if (mGravitySpeed > -10000.0f)
		mGravitySpeed -= 100.0f;

	mMoveComponent->setUpSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getUp()));
	mMoveComponent->setForwardSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getForward()));
	mMoveComponent->setSideSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getSide()));
}

void Player::collides(const std::weak_ptr<BoxComponent>& bComp)
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

void Player::setPlayerTexture(const std::string& fileName)
{
	auto index = static_cast<int>(mType);
	mMeshComponent->setTexture(fileName);
	mMeshComponent->setTextureIndex(index);
	mLeftArm->setPlayerTexture(fileName, index);
	mRightArm->setPlayerTexture(fileName, index);
	mLeftLeg->setPlayerTexture(fileName, index);
	mRightLeg->setPlayerTexture(fileName, index);
	mHead->setPlayerTexture(fileName, index);
}