#pragma once
#include "../../Game/UI/UI.h"

class PauseUI : public UI
{
public:
	enum class UIType
	{
		Pause,
		Clear
	};

	PauseUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, UIType type = UIType::Pause);
	virtual ~PauseUI() noexcept;

	virtual void initailize();

	virtual void processInput();

	void goToTitle();

private:
	UIType mType;
};