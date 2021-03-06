#pragma once
#include <memory>
#include <gl/freeglut.h>
#include "..\Math\Math.h"

class Mouse final
{
private:
	static constexpr auto Button_Max = 3;
	static bool mState[Button_Max];
	static bool mFirst[Button_Max];
	static Vector2 mOriginPosition;
	static Vector2 mPosition;
	static bool mWarp;

public:
	Mouse();
	~Mouse() noexcept;

	void initialize();
	void update();

	bool getState(int button) const { return mState[button]; }
	bool getFirst(int button) const { return mFirst[button]; }
	const Vector2& getOriginPosition() const { return mOriginPosition; }
	const Vector2& getPosition() const { return mPosition; }

	void setWarp(bool warp) { mWarp = warp; }
	void setCursor(int cursor) { glutSetCursor(cursor); }

private:
	friend GLvoid mouseClickCallBack(int button, int state, int x, int y);
	friend GLvoid mouseClickMoveCallBack(int x, int y);
	friend GLvoid mouseMoveCallBack(int x, int y);
};