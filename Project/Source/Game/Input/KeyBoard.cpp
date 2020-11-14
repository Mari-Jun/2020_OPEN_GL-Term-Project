#include "KeyBoard.h"
#include <iostream>

GLvoid keyDownCallBack(unsigned char key, int x, int y);
GLvoid keyUpCallBack(unsigned char key, int x, int y);
GLvoid specialKeyDownCallBack(int key, int x, int y);
GLvoid specialKeyUpCallBack(int key, int x, int y);

bool KeyBoard::mKeys[KeyBoard::Key_Max] = { false };
bool KeyBoard::mFirsts[KeyBoard::Key_Max] = { false };
std::unordered_map<int, bool> KeyBoard::mSpecialKeys = 
{ 
	{GLUT_KEY_UP,false},{GLUT_KEY_DOWN,false},
	{GLUT_KEY_LEFT,false},{GLUT_KEY_LEFT,false}
};

KeyBoard::KeyBoard()
{
	this->initalize();
}

KeyBoard::~KeyBoard()
{

}

void KeyBoard::initalize()
{
	//Set CallBack
	glutKeyboardFunc(keyDownCallBack);
	glutKeyboardUpFunc(keyUpCallBack);
	glutSpecialFunc(specialKeyDownCallBack);
	glutSpecialUpFunc(specialKeyUpCallBack);
}

GLvoid keyDownCallBack(unsigned char key, int x, int y)
{
	KeyBoard::mKeys[static_cast<int>(key)] = true;
	KeyBoard::mFirsts[static_cast<int>(key)] = true;
}

GLvoid keyUpCallBack(unsigned char key, int x, int y)
{
	KeyBoard::mKeys[static_cast<int>(key)] = false;
	KeyBoard::mFirsts[static_cast<int>(key)] = false;
}

GLvoid specialKeyDownCallBack(int key, int x, int y)
{
	KeyBoard::mSpecialKeys[key] = true;
}

GLvoid specialKeyUpCallBack(int key, int x, int y)
{
	KeyBoard::mSpecialKeys[key] = false;
}