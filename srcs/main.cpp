#include "scop.hpp"


int	main(int argc, char **argv, char **envp)
{
	GLFWwindow* window;
	std::vector<std::vector<std::string>>	file;
	try
	{
		checkArgument(argc, argv[1]);
		std::ifstream	infile = openFile(argv[1]);

		for (std::string line; std::getline(infile, line);)
		{
			std::vector<std::string>	words = split(line, " ");
			if (std::strcmp(words[0].c_str(), "#") == 0 || words.empty())
				continue;
			file.push_back(words);
		}
		infile.close();

		window = initWindow();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}




	float	vertexes[6] = {
		 0.5,  0.5,
		-0.5,  0.5,
		 0.0, -0.5
	};
	unsigned int buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexes, GL_STATIC_DRAW);

	// Telling how to interpret the buffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	int	width = 0;
	int	height = 0;
	while(!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
