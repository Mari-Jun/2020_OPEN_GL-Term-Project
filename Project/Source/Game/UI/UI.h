#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "../Math/Math.h"

class UI : public std::enable_shared_from_this<UI>
{
public:
	enum class UIState
	{
		Active,
		Dead
	};

	UI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render);
	virtual ~UI() noexcept;

	virtual void initailize();

	virtual void update(float deltatime);
	virtual void processInput();
	virtual void draw(std::unique_ptr<class Shader>& shader);

	void update(float deltatime);
	void processInput();
	void draw(std::unique_ptr<class Shader>& shader);

	void drawTexture(std::unique_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& texture, const Vector2& pos);
	void addButton(std::function<void()> click, const Vector2& pos, const std::shared_ptr<class Texture>& texture);

	void closeUI();

protected:
	UIState mState;
	std::weak_ptr<class Scene> mScene;
	std::weak_ptr<class Renderer> mRenderer;
	std::vector<std::shared_ptr<class Button>> mButtons;

public:
	UIState getState() const { return mState; }
	void setBackgroundTexture(const std::shared_ptr<class Texture>& texture) { mBackground = texture; }
};
