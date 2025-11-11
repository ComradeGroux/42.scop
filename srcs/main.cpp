#include <iostream>

// Basic OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>

// Windows and events management
#include <GLFW/glfw3.h>

int main(int argc, char **argv, char **envp)
{
	if(argc < 2 || argc > 2)
	{
		std::cerr << "You need to provide one object" << std::endl;
		return -1;
	}

	if(!glfwInit())
		return -1;

	GLFWwindow*	window;
	window = glfwCreateWindow(640, 480, "scop", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
