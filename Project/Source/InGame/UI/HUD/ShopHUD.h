#pragma once
#include "../../../Game/UI/UI.h"

using vTexSet = std::vector<std::shared_ptr<class Texture>>;

struct StatNumber
{
	vTexSet mHpNumber;
	vTexSet mDefNumber;
	vTexSet mSpeedNumber;
};

class ShopHUD : public UI
{
public:
	

	ShopHUD(const std::weak_ptr<class ShopScene>& scene, const std::weak_ptr<class Renderer>& render);
	~ShopHUD();

	virtual void initailize();

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

private:
	void loadCoinNumber();
	void loadPlayerStat();
	void loadMinionStat();

	void setNumberTexture(vTexSet& texture, int info, const std::string& fileName);
	void drawNumberTexture(std::unique_ptr<class Shader>& shader, const vTexSet& texture, const Vector2& pos, float gap);
};