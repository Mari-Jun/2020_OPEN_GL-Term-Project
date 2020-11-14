#include "Window.h"

GLvoid renderCallBack();
GLvoid reshapeCallBack(int width, int height);
GLvoid entryCallBack(int state);

Vector2 Window::mPosition = Vector2(100.0f, 100.0f);
Vector2 Window::mSize = Vector2(1366.0f, 768.0f);
int Window::mEntry = GLUT_ENTERED;

Window::Window(const Vector2& size, std::string& name)
	: mName(name)
{
	mSize = size;
	mPosition.x = (glutGet(GLUT_SCREEN_WIDTH) - mSize.x) / 2;
	mPosition.y = (glutGet(GLUT_SCREEN_HEIGHT) - mSize.y) / 2;
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
	glutEntryFunc(entryCallBack);

	return true;
}

void Window::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mPosition.x = glutGet((GLenum)GLUT_WINDOW_X);
	mPosition.y = glutGet((GLenum)GLUT_WINDOW_Y);
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
	glViewport(0, 0, Window::mSize.x, Window::mSize.y);
}

GLvoid entryCallBack(int state)
{
	Window::mEntry = state;
	std::cout << state << std::endl;
}