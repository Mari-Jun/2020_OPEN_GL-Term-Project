#pragma once
#include <memory>
#include <vector>

class UI
{
public:
	UI(const std::weak_ptr<class Scene>& scene);
	virtual ~UI() noexcept;

	void update(float deltatime);
	void processInput();
	void draw();

private:
	std::vector<std::shared_ptr<class Button>> mButtons;
};

//스택으로 가도 나쁘지는 않을듯?
