#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

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

std::vector<std::string>	split(std::string& str, const std::string& del)
{
	std::vector<std::string>	tokens;
	size_t						pos = 0;
	std::string					tok;

	while ((pos = str.find(del)) != std::string::npos)
	{
		tok = str.substr(0, pos);
		tokens.push_back(tok);
		str.erase(0, pos + del.length());
	}
	tokens.push_back(str);

	return tokens;
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

	std::ifstream infile(argv[1], std::ios::in);
	if (!infile.is_open())
	{
		std::cerr << "Error: File does not exist" << std::endl;
		return -1;
	}

	std::vector<std::vector<std::string>>	file;
	for (std::string line; std::getline(infile, line);)
	{
		std::vector<std::string>	words = split(line, " ");
		if (std::strcmp(words[0].c_str(), "#") == 0)
			continue;
		file.push_back(words);
	}
	size_t	length = file.size();
	for (size_t i = 0; i < length; i++)
	{
		size_t	l = file[i].size();
		for (size_t j = 0; j < l; j++)
		{
			std::cout << file[i][j] << " ";
		}
		std::cout << std::endl;
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
