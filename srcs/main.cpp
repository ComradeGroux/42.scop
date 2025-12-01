#include "scop.hpp"


int	main(int argc, char **argv, char **envp)
{
	GLFWwindow* 							window;

	std::vector<Vec3>						pos_vertex;
	std::vector<std::vector<int>>			fac_vertex;
	std::string								materialFile;


	try
	{
		checkArgument(argc, argv[1]);
		std::ifstream	infile = openFile(argv[1]);

		unsigned int	jFac = 0;
		std::string syntax_error = "Syntax error in ";
		syntax_error += argv[1];
		for (std::string line; std::getline(infile, line);)
		{
			std::vector<std::string>	words = split(line, " ");
			int size = words.size();
			switch (hashit(words[0]))
			{
				case eComment:
					continue;

				case eVertex:
					if (size >= 4)
					{
						Vec3 pos = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
						if (size == 5)
							pos.w = std::stof(words[4]);
						else if (size > 5)
							throw std::invalid_argument(syntax_error);
						pos.x /= pos.w;
						pos.y /= pos.w;
						pos.z /= pos.w;
						pos_vertex.push_back(pos);
					}
					else
						throw std::invalid_argument(syntax_error);
					continue;

				case eFaces:
					for (unsigned int i = 1; i < words.size(); i++)
					{
						fac_vertex.push_back({});
						fac_vertex[jFac].push_back(std::stoi(words[i]));
					}
					jFac++;
					continue;

				case eMatLib:
					materialFile = words[1];
					continue;

				case eUseMatLib:
				case eName:
				case eSmooth:
				case eDefault:
					continue;
				default:
					std::cerr << "Error: no case for \"" << words[0] << "\"" << std::endl;
					break;
			}
		}
		infile.close();

		window = initWindow();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}




	enum { POSITION, COLOR, NUM_BUFF };
	float	vertexes[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};
	float	colors[12] = {
		1.0f,	0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,	0.0f,	1.0f,
		0.0f,	0.0f,	1.0f,	1.0f
	};

	unsigned int vao, vbo[NUM_BUFF];
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(NUM_BUFF, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_ATTRIB_LOC);
	glVertexAttribPointer(POSITION_ATTRIB_LOC, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(COLOR_ATTRIB_LOC);
	glVertexAttribPointer(COLOR_ATTRIB_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	std::string vertex = readFullFile("shaders/basic.vrt");
	std::string fragment = readFullFile("shaders/basic.frg");
	unsigned int program = createShader(vertex, fragment);

	int	width = 0;
	int	height = 0;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while(!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(program);
	glfwMakeContextCurrent(nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
