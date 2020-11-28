#pragma once
#include "../../../Game/UI/UI.h"

using vTexSet = std::vector<std::shared_ptr<class Texture>>;

class HUD : public UI
{
public:
	HUD(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render);
	~HUD();

	virtual void initailize();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

	void setNumberTexture(vTexSet& texture, int info, const std::string& fileName);
	void drawNumberTexture(std::unique_ptr<class Shader>& shader, const vTexSet& texture, const Vector2& pos, float gap);
};