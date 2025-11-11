#include <iostream>
#include <cstring>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

void	error_callback(int error, const char* description)
{
	std::cerr << "Error " << error << ": " << description << std::endl;
}

int checkFileExtension(char *file)
{
	std::size_t found = std::string(file).find_last_of(".");
	return strcmp(file + found, ".obj");
}

int	main(int argc, char **argv, char **envp)
{
	if(argc < 2 || argc > 2)
	{
		std::cerr << "Error: Wrong number of arguments" << std::endl;
		return -1;
	}
	if (checkFileExtension(argv[1]) != 0)
	{
		std::cerr << "Error: Wrong extension" << std::endl;
		return -1;
	}
















	glfwSetErrorCallback(error_callback);
	if(glfwInit() != GLFW_TRUE)
		return -1;

	GLFWwindow*	window = glfwCreateWindow(640, 480, "scop", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
