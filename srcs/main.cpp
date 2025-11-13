#include "scop.hpp"


int	main(int argc, char **argv, char **envp)
{
	std::vector<std::vector<std::string>>	file;
	try
	{
		checkArgument(argc, argv[1]);
		std::ifstream	infile = openFile(argv[1]);

		for (std::string line; std::getline(infile, line);)
		{
			std::vector<std::string>	words = split(line, " ");
			if (std::strcmp(words[0].c_str(), "#") == 0)
				continue;
			file.push_back(words);
		}
		infile.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}
	printVectorVectorString(file);









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
