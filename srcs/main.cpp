#include "scop.hpp"

int	main(int argc, char **argv, char **envp)
{
	GLFWwindow*		window;
	Object			obj;
	try
	{
		checkArgument(argc, argv[1]);
		initObjet(argv[1], obj);

		window = initWindow();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}






	unsigned int vao, vbo[NUM_BUFF];
	cgl(glGenVertexArrays(1, &vao));
	cgl(glBindVertexArray(vao));
	cgl(glGenBuffers(NUM_BUFF, vbo));

	std::string vertexShader = readFullFile("shaders/basic.vrt");
	std::string fragmentShader = readFullFile("shaders/basic.frg");
	unsigned int program = createShader(vertexShader, fragmentShader);

	int	width = 0;
	int	height = 0;
	float r = 0.5f;
	float increment = 0.05f;

	cgl(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	while(!glfwWindowShouldClose(window))
	{
		cgl(glfwGetFramebufferSize(window, &width, &height));
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		r = 0.55f;
		increment = 0.1f;
		for (unsigned int i = 0; i < obj.triangles.size(); i++)
		{
			drawTriangle(program,
					vao,
					vbo,
					obj.triangles[i][0],
					obj.triangles[i][1],
					obj.triangles[i][2],
					r);

			if (r > 0.9f)
				increment = -0.05f;
			else if (r < 0.1f)
				increment = 0.05f;
			r += increment;
		}

		cgl(glfwSwapBuffers(window));
		cgl(glfwPollEvents());
	}

	cgl(glDeleteProgram(program));
	cgl(glfwMakeContextCurrent(nullptr));
	cgl(glfwDestroyWindow(window));
	glfwTerminate();
	return 0;
}

void drawTriangle(unsigned int shaderToUse, unsigned int vao, unsigned int vbo[NUM_BUFF], Vertex a, Vertex b, Vertex c, float baseColor)
{
	cgl(glUseProgram(shaderToUse));
	cgl(glBindVertexArray(vao));

	float vertexes[9] = {
		a.x, a.y, a.z,
		b.x, b.y, b.z,
		c.x, c.y, c.z
	};

	float	colors[12] = {
		baseColor, baseColor, baseColor, 1.0f,
		baseColor, baseColor, baseColor, 1.0f,
		baseColor, baseColor, baseColor, 1.0f
	};

	cgl(glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION]));
	cgl(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW));
	cgl(glEnableVertexAttribArray(POSITION_ATTRIB_LOC));
	cgl(glVertexAttribPointer(POSITION_ATTRIB_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));

	cgl(glBindBuffer(GL_ARRAY_BUFFER, vbo[COLOR]));
	cgl(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
	cgl(glEnableVertexAttribArray(COLOR_ATTRIB_LOC));
	cgl(glVertexAttribPointer(COLOR_ATTRIB_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0));

	cgl(glDrawArrays(GL_TRIANGLES, 0, 3));
}
