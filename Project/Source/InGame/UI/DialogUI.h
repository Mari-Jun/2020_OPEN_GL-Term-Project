#pragma once
#include "../../Game/UI/UI.h"

class DialogUI : public UI
{
public:
	DialogUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render);
	virtual ~DialogUI() noexcept;

	virtual void initailize();

	virtual void processInput();
};