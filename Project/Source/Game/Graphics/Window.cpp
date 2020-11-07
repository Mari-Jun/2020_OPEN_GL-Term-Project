#include "Window.h"

GLvoid renderCallBack();
GLvoid reshapeCallBack(int width, int height);

Vector2 Window::mPosition = Vector2(0.0f, 0.0f);
Vector2 Window::mSize = Vector2(800.0f, 600.0f);

Window::Window(const Vector2& pos, const Vector2& size, std::string& name)
	: mName(name)
{
	mPosition = pos;
	mSize = size;
}

Window::~Window()
{

}

bool Window::initialize()
{
	//Create Window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(static_cast<int>(mPosition.x), static_cast<int>(mPosition.y));
	glutInitWindowSize(static_cast<int>(mSize.x), static_cast<int>(mSize.y));
	glutCreateWindow(mName.c_str());

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		return false;
	}
	else
	{
		std::cout << "GLEW initailized\n";
	}

	//Set CallBack
	glutDisplayFunc(renderCallBack);
	glutReshapeFunc(reshapeCallBack);

	//Set Mouse Position
	glutWarpPointer(static_cast<int>(mSize.x / 2), static_cast<int>(mSize.y / 2));
	RECT rect{ static_cast<int>(mPosition.x),static_cast<int>(mPosition.y),static_cast<int>(mSize.x), static_cast<int>(mSize.y) };
	ClipCursor(&rect);

	return true;
}

void Window::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffer() 
{
	glutSwapBuffers();
	glutMainLoopEvent();
}

GLvoid renderCallBack()
{
	
}

GLvoid reshapeCallBack(int width, int height)
{

}
