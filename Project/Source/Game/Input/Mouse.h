#pragma once
#include <memory>
#include <gl/freeglut.h>
#include "..\Math\Math.h"

class Mouse final
{
private:
	static constexpr auto Button_Max = 3;
	static bool mState[Button_Max];
	static Vector2 mOriginPosition;
	static Vector2 mPosition;

public:
	Mouse();
	~Mouse() noexcept;

	void initialize();

	bool getState(int button) const { return mState[button]; }
	const Vector2& getOriginPosition() const { return mOriginPosition; }
	const Vector2& getPosition() const { return mPosition; }


private:
	friend GLvoid mouseClickCallBack(int button, int state, int x, int y);
	friend GLvoid mouseClickMoveCallBack(int x, int y);
	friend GLvoid mouseMoveCallBack(int x, int y);
};