#include "MovePlayer.h"
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

MovePlayer::MovePlayer(const std::weak_ptr<class Scene>& scene, PlayerInfo info)
	: Player(scene, info)
	, mStat({})
	, mGravitySpeed(0.0f)
{

}

MovePlayer::~MovePlayer()
{
	mHealthBar->setState(Actor::State::Dead);
}

void MovePlayer::initailize()
{
	Player::initailize();

	//Create MoveComponent
	mMoveComponent = std::make_shared<MoveComponent>(weak_from_this());
	mMoveComponent->initailize();

	//Create BoxComponent
	mBoxComponent = std::make_shared<BoxComponent>(weak_from_this(), getGame().lock()->getPhysEngine());
	mBoxComponent->setObjectBox(mMeshComponent->getMesh()->getBox());
	mBoxComponent->initailize();

	//Create HealthBar
	mHealthBar = std::make_shared<Actor>(getScene(), Type::Ui);
	auto hp = std::make_shared<BillBoardComponent>(mHealthBar, getGame().lock()->getRenderer());
	hp->setTexture(getGame().lock()->getRenderer()->getTexture("Asset/Image/Player/RedBar.png"));
	hp->initailize();
	mHealthBar->setScale(0.1f);
	mHealthBar->initailize();
}

void MovePlayer::updateActor(float deltatime)
{
	Player::updateActor(deltatime);

	updateGravity(deltatime);

	collides(mBoxComponent);

	mHealthBar->setScale(Vector3(0.1f, 0.1f, 0.1f) - 0.1f * Vector3(1.0f, 0.0f, 1.0f) * (1.0f - (mStat.mHp) / mStat.mMaxHp));
	mHealthBar->setPosition(getPosition() + Vector3::UnitY * 30.0f);
}

void MovePlayer::updateAnimation()
{
	mLeftArm->setMove(true);
	mRightArm->setMove(true);
	mLeftLeg->setMove(true);
	mRightLeg->setMove(true);
}

void MovePlayer::actorInput()
{
	
}

void MovePlayer::updateGravity(float deltatime)
{
	//중력 설정
	if (mGravitySpeed > -10000.0f)
		mGravitySpeed -= 100.0f;

	mMoveComponent->setUpSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getUp()));
	mMoveComponent->setForwardSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getForward()));
	mMoveComponent->setSideSpeed(mGravitySpeed * deltatime * Vector3::Dot(Vector3::UnitY, getSide()));
}

void MovePlayer::collides(const std::weak_ptr<BoxComponent>& bComp)
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

void MovePlayer::setStat(PlayerInfo info)
{

}

void MovePlayer::decreaseHp(float damage)
{
	damage = damage - damage / 100.0f * 5 * mStat.mDef;
	mStat.mHp = Math::Max(mStat.mHp - damage, 0.0f);
}

void MovePlayer::increaseHp(float hill)
{
	mStat.mHp = Math::Min(mStat.mHp + hill, mStat.mMaxHp);
}