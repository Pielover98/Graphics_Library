#include "graphics\Context.h"
#include "graphics/glinc.h"

#ifdef _DEBUG
#include <iostream>
void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cerr << message << std::endl;
}
#endif
bool Context::getKey(int Key)
{
	return glfwGetKey(handle, Key);
}

bool Context::getMouseButton(int button)
{
	return glfwGetMouseButton(handle, button);
}

void Context::getMousePosition(double & x_out, double & y_out)
{
	glfwGetCursorPos(handle, &x_out, &y_out);
}



double Context::getTime()
{

	return glfwGetTime();
}

bool Context::init(size_t width, size_t height, const char * title)
{
	glfwInit();

	handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(handle);

	glewExperimental = true;
	glewInit();

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif


	return true;
}

bool Context::step()
{
	glfwPollEvents();
	glfwSwapBuffers(handle);


	return !glfwWindowShouldClose(handle);
}

bool Context::term()
{
	glfwTerminate();
	handle = nullptr;
	return true;
}

