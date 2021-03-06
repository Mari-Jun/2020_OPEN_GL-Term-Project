#pragma once
#include "HUD.h"

using vTexSet = std::vector<std::shared_ptr<class Texture>>;

struct StatNumber
{
	vTexSet mHpNumber;
	vTexSet mDefNumber;
	vTexSet mSpeedNumber;
};

class ShopHUD : public HUD
{
public:

	ShopHUD(const std::weak_ptr<class ShopScene>& scene, const std::weak_ptr<class Renderer>& render);
	~ShopHUD();

	virtual void initailize();
	virtual void resetInfo();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

private:
	std::weak_ptr<class ShopScene> mShopScene;
	std::shared_ptr<class Texture> mCoin;
	vTexSet mCoinNumber;
	std::shared_ptr<class Texture> mReinForceBoard;
	StatNumber mPlayerStat;
	StatNumber mMinionStat;
	std::shared_ptr<class Texture> mSkin1;
	std::shared_ptr<class Texture> mSkin2;

private:
	void loadCoinNumber();
	void loadStat(const struct PlayerInfo& info, StatNumber& stat);
};