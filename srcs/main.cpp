#include <iostream>

// Basic OpenGL includes
#include <GL/gl.h>
#include <GL/glu.h>

// Windows and events management
#include <GLFW/glfw3.h>

int main(int argc, char **argv, char **envp)
{
	if (argc < 2 || argc > 2)
	{
		std::cerr << "You need to provide one object" << std::endl;
		return -1;
	}
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	return 0;
}
