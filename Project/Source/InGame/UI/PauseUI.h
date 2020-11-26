#pragma once
#include "../../Game/UI/UI.h"

class PauseUI : public UI
{
public:
	PauseUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render);
	virtual ~PauseUI() noexcept;

	virtual void initailize();

	virtual void processInput();

	void goToTitle();
};