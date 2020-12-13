#pragma once
//¹Ì´Ï¸Ê.h
#include <memory>
#include <vector>
#include <functional>
#include "../Math/Math.h"

class Minimap : public std::enable_shared_from_this<Minimap>
{
public:

	Minimap(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class Renderer>& render, const std::weak_ptr<class Actor>& owner, bool standard);
	virtual ~Minimap() noexcept;

	virtual void initailize();

	virtual void update(float deltatime);
	virtual void draw(std::unique_ptr<class Shader>& shader);

	void setTexture(const std::shared_ptr<class Texture>& texture);
	void drawTexture(std::unique_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& texture, const Vector2& pos);
	void drawTexture(std::unique_ptr<class Shader>& shader, const Vector2& pos);
	void drawTexture(std::unique_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& texture, const Vector3& pos);

protected:
	std::weak_ptr<class Scene> mScene;
	std::weak_ptr<class Renderer> mRenderer;
	std::weak_ptr<class Actor> mOwner;

	std::shared_ptr<class Texture> mBackground;
	Vector2 mBackgroundPos;

	std::shared_ptr<class Texture> mTexture;
	Vector2 mPosition;
	int mTexWidth;
	int mTexHeight;
	Vector2 mMapSize;
	Vector2 mMinimapSize;
	static std::weak_ptr<class Actor> mStandard;
public:
	void setMapSize(Vector2 mapsize) { mMapSize = mapsize; }
	const Vector2& getMapSize() const { return mMapSize; }
	void setMinimapSize(Vector2 minimapsize) { mMinimapSize = minimapsize; }
	const Vector2& getMiniMapSize() const { return mMinimapSize; }
	void setTexSize(int Width, int Height) { mTexWidth = Width, mTexHeight = Height; }

private:

};