#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "../Math/Math.h"

class UI : public std::enable_shared_from_this<UI>
{
public:
	enum class State
	{
		Active,
		Dead
	};

	UI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render);
	virtual ~UI() noexcept;

	void initailize();

	void update(float deltatime);
	void processInput();
	void draw(std::unique_ptr<class Shader>& shader);

	void addButton(std::function<void()> click, const Vector2& pos, const std::shared_ptr<class Texture>& texture);

private:
	State mState;
	std::weak_ptr<class Scene> mScene;
	std::weak_ptr<class Renderer> mRenderer;
	std::vector<std::shared_ptr<class Button>> mButtons;

public:
	State getState() const { return mState; }
};

//스택으로 가도 나쁘지는 않을듯?
