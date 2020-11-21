#pragma once
#include "../../Game/UI/UI.h"

class TitleUI : public UI
{
public:
	TitleUI(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render);
	virtual ~TitleUI() noexcept;

	virtual void initailize();

	virtual void processInput();
};