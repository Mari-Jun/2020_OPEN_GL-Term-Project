#pragma once
#include "../../Game/UI/UI.h"


class NotYetUI : public UI
{
public:
	NotYetUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render);
	virtual ~NotYetUI() noexcept;

	virtual void initailize();

	virtual void processInput();
};