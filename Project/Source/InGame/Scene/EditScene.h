#pragma once
#include "../../Game/Scene/Scene.h"
#include "../../Game/Math/Math.h"

class EditScene : public Scene
{
public:
	EditScene(const std::weak_ptr<class Game>& game, int stage = 1);
	virtual ~EditScene();

	virtual void initailize();

	virtual void sceneInput();
	virtual void sceneUpdate(float deltatime);

	virtual void loadData();
	virtual void unLoadData();
	bool loadGameMap();
	void loadBoard();

private:
	std::shared_ptr<class GameMap> mGameMap;
	std::unique_ptr<class MapEditor> mEditor;
	std::unique_ptr<class SceneHelper> mSceneHelper;
	int mStage;

	Vector2 mLeftBoardPos;
	Vector2 mLeftBoardTexSize;
	Vector2 mRightBoardPos;
	Vector2 mRightBoardTexSize;
	Vector2 mSaveButtonPos;
	Vector2 mButtonSize;

public:
	const Vector2& getLeftBoardPos() const { return mLeftBoardPos; }
	const Vector2& getLeftBoardTexSize() const { return mLeftBoardTexSize; }
	const Vector2& getRightBoardPos() const { return mRightBoardPos; }
	const Vector2& getRightBoardTexSize() const { return mRightBoardTexSize; }
};
