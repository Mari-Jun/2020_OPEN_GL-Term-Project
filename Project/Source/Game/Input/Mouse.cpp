#include "../Graphics/Renderer/Renderer.h"
#include "../Graphics/Window.h"
#include "Mouse.h"
#include <iostream>

GLvoid mouseClickCallBack(int button, int state, int x, int y);
GLvoid mouseClickMoveCallBack(int x, int y);
GLvoid mouseMoveCallBack(int x, int y);

bool Mouse::mState[Mouse::Button_Max] = { false, };
bool Mouse::mFirst[Button_Max] = { false, };
Vector2 Mouse::mOriginPosition;
Vector2 Mouse::mPosition;
bool Mouse::mWarp = false;

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
}

void Mouse::update()
{
	for (auto& bt : Mouse::mFirst)
	{
		bt = false;
	}
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
	if (Window::getEntry())
	{
		RECT rect{ Window::getPosition().x, Window::getPosition().y - 10,
		 Window::getPosition().x + static_cast<LONG>(Window::getSize().x),
		 Window::getPosition().y + static_cast<LONG>(Window::getSize().y) };

		ClipCursor(&rect);
	}
	
	if (Mouse::mWarp)
	{
		glutWarpPointer(static_cast<int>(Window::getSize().x / 2), static_cast<int>(Window::getSize().y / 2));
		Mouse::mPosition = Vector2(0.0f, 0.0f);
		Mouse::mOriginPosition = Mouse::mPosition;
	}

	Mouse::mPosition.x = static_cast<float>(x) - Window::getSize().x / 2.0f;
	Mouse::mPosition.y = (static_cast<float>(y) - Window::getSize().y / 2.0f) /** -1.0f*/;
}