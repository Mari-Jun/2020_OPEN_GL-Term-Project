#include "../Graphics/Renderer/Renderer.h"
#include "../Graphics/Window.h"
#include "Mouse.h"
#include <iostream>

GLvoid mouseClickCallBack(int button, int state, int x, int y);
GLvoid mouseClickMoveCallBack(int x, int y);
GLvoid mouseMoveCallBack(int x, int y);

bool Mouse::mState[Mouse::Button_Max] = { false };
Vector2 Mouse::mOriginPosition;
Vector2 Mouse::mPosition;

Mouse::Mouse()
{
	this->initialize();
}

Mouse::~Mouse()
{

}

void Mouse::initialize()
{
	//Set CallBack
	glutMouseFunc(mouseClickCallBack);
	glutMotionFunc(mouseMoveCallBack);
	glutPassiveMotionFunc(mouseMoveCallBack);

	glutSetCursor(GLUT_CURSOR_NONE);
}

void Mouse::update()
{
	mOriginPosition = mPosition;
}

void Mouse::resetMousePosition()
{
	glutWarpPointer(static_cast<int>(Window::getSize().x / 2), static_cast<int>(Window::getSize().y / 2));
	mPosition = Vector2(0.0f, 0.0f);
	mOriginPosition = mPosition;
	
}

GLvoid mouseClickCallBack(int button, int state, int x, int y)
{
	Mouse::mState[button] = (state == GLUT_DOWN);
}

GLvoid mouseClickMoveCallBack(int x, int y)
{
	
}

GLvoid mouseMoveCallBack(int x, int y)
{
	Mouse::mPosition.x = static_cast<float>(x) - Window::getSize().x / 2.0f;
	Mouse::mPosition.y = (static_cast<float>(y) - Window::getSize().y / 2.0f) /** -1.0f*/;
}