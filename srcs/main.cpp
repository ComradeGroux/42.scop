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

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int	checkFileExtension(char *file)
{
	std::size_t found = std::string(file).find_last_of(".");
	return strcmp(file + found, ".obj");
}

int	main(int argc, char **argv, char **envp)
{
	if(argc != 2)
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
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);

	int	width = 0;
	int height = 0;
	while(!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
