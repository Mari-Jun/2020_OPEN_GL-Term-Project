#pragma once
#include "../../Game/Minimap/Minimap.h"


class GameMinimap : public Minimap
{
public:

	GameMinimap(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, const std::weak_ptr<class Actor>& owner, bool standard = false);
	virtual ~GameMinimap() noexcept;

	virtual void initailize();

	virtual void update(float deltatime);
	virtual void draw(std::unique_ptr<class Shader>& shader);

private:
	std::shared_ptr<class Texture> mPlayerMarker;

};