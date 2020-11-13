#include "Window.h"

GLvoid renderCallBack();
GLvoid reshapeCallBack(int width, int height);

Vector2 Window::mPosition = Vector2(100.0f, 100.0f);
Vector2 Window::mSize = Vector2(1366.0f, 768.0f);

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
