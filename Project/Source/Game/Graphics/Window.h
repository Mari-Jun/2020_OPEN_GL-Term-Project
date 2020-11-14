#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include "../Math/Math.h"

class Window
{
public:
	Window(const Vector2& pos, const Vector2& size, std::string& name);
	~Window() noexcept;

	bool initialize();

private:
	static Vector2 mPosition;
	static Vector2 mSize;
	static int mEntry;
	std::string mName;

public:
	void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f);

	void swapBuffer();

	static Vector2 getPosition() { return mPosition; }
	static Vector2 getSize() { return mSize; }
	static int getEntry() { return mEntry; }

private:
	friend GLvoid renderCallBack();
	friend GLvoid reshapeCallBack(int width, int height);
	friend GLvoid entryCallBack(int state);
};


