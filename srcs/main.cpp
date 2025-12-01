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




	float	vertexes[9] = {
		-0.5f, -0.5f,  0.0f,
		 0.0f,  0.5f,  1.0f,
		 0.5f, -0.5f, -1.0f
	};
	float	colors[12] = {
		1.0f,	0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,	0.0f,	1.0f,
		0.0f,	0.0f,	1.0f,	1.0f
	};

	unsigned int vao, vbo[NUM_BUFF];
	cgl(glGenVertexArrays(1, &vao));
	cgl(glBindVertexArray(vao));
	cgl(glGenBuffers(NUM_BUFF, vbo));

	cgl(glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION]));
	cgl(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW));
	cgl(glEnableVertexAttribArray(POSITION_ATTRIB_LOC));
	cgl(glVertexAttribPointer(POSITION_ATTRIB_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));

	cgl(glBindBuffer(GL_ARRAY_BUFFER, vbo[COLOR]));
	cgl(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
	cgl(glEnableVertexAttribArray(COLOR_ATTRIB_LOC));
	cgl(glVertexAttribPointer(COLOR_ATTRIB_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0));

	std::string vertex = readFullFile("shaders/basic.vrt");
	std::string fragment = readFullFile("shaders/basic.frg");
	unsigned int program = createShader(vertex, fragment);

	int	width = 0;
	int	height = 0;
	cgl(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	while(!glfwWindowShouldClose(window))
	{
		cgl(glfwGetFramebufferSize(window, &width, &height));
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		cgl(glUseProgram(program));
		cgl(glBindVertexArray(vao));
		cgl(glDrawArrays(GL_TRIANGLES, 0, 3));

		cgl(glfwSwapBuffers(window));
		cgl(glfwPollEvents());
	}

	cgl(glDeleteProgram(program));
	cgl(glfwMakeContextCurrent(nullptr));
	cgl(glfwDestroyWindow(window));
	glfwTerminate();
	return 0;
}
