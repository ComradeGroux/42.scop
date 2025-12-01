#include "scop.hpp"

void	checkArgument(int argc, char *file)
{
	if(argc != 2)
		throw std::invalid_argument("Wrong number of argument");

	std::size_t found = std::string(file).find_last_of(".");
	if (strcmp(file + found, ".obj") != 0)
		throw std::invalid_argument("Wrong extension (must be .obj)");
}

GLFWwindow*	initWindow()
{
	if(glfwInit() != GLFW_TRUE)
		throw std::runtime_error("GLFW init goes wrong");
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	GLFWwindow*	window = glfwCreateWindow(WIDTH, HEIGHT, "scop", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		throw std::runtime_error("The window's creation failed");
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		throw std::runtime_error("An issue occured during the loading of GLAD");
	}

	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);

	return window;
}

e_line_type	hashit(std::string const& inString)
{
	if (inString == "#")
		return eComment;
	if (inString == "v")
		return eVertex;
	if (inString == "f")
		return eFaces;
	if (inString.empty())
		return eComment;
	if (inString == "o")
		return eName;
	if (inString == "usemtl")
		return eUseMatLib;
	if (inString == "mtllib")
		return eMatLib;
	if (inString == "s")
		return eSmooth;

	return eDefault;
}
