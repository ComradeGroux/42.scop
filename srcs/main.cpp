#include "Object.hpp"

#include "scop.hpp"

static void	renderer(GLFWwindow* window, Object& obj);

int	main(int argc, char **argv, char **envp)
{
	Object		obj;
	GLFWwindow*	window = initWindow(argc, argv, envp);

	if (!window)
		exit(-1);
	if (obj.load(argv[1]) != 0)
		exit(-1);

	renderer(window, obj);

	glfwDestroyWindow(window);
	glfwMakeContextCurrent(nullptr);
	glfwTerminate();
	return 0;
}

static void	renderer(GLFWwindow* window, Object& obj)
{
// /*
	std::vector<Vertex>	tmp = obj.getVertices();
	std::vector<float>	vectorFloat;
	for (unsigned int i = 0; i < tmp.size(); i++)
	{
		vectorFloat.push_back(tmp[i].x);
		vectorFloat.push_back(tmp[i].y);
		vectorFloat.push_back(tmp[i].z);
	}
	float*	rawPos = vectorFloat.data();
	// float rawPos[vectorFloat.size()];
	// for (unsigned int i = 0; i < vectorFloat.size(); i++)
		// rawPos[i] = vectorFloat[i];

	std::vector<std::vector<unsigned int>>	tmp1 = obj.getFaces();
	std::vector<unsigned int>				vectorInt;
	for (unsigned int i = 0; i < tmp1.size(); i++)
	{
		if (tmp1.size() != 3)
			continue;
		for (unsigned int j = 0; j < tmp1[i].size(); j++)
			vectorInt.push_back(tmp1[i][j]);
	}
	unsigned int* rawIndex = vectorInt.data();
	// unsigned int rawIndex[vectorInt.size()];
	// for (unsigned int i = 0; i < vectorInt.size(); i++)
	// 	rawIndex[i] = vectorInt[i];
// */

	// float rawPos[12] = {
	// 	0.232406f, -1.216630f, 1.133818f,
	// 	0.232406f, -0.745504f, 2.843098f,
	//    -0.227475f, -0.745504f, 2.843098f,
	//    -0.227475f, -1.216630f, 1.133818f
	// };
	// unsigned int rawIndex[6] = {
	// 	1, 2, 3,
	// 	1, 3, 4
	// };

	unsigned int vao;
	cgl(glGenVertexArrays(1, &vao));
	cgl(glBindVertexArray(vao));

	VertexBuffer vb(rawPos, vectorFloat.size());
	cgl(glEnableVertexAttribArray(POSITION_ATTRIB_LOC));
	cgl(glVertexAttribPointer(POSITION_ATTRIB_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));

	float	colors[] = {
		1.0f, 0.5f, 0.5f, 1.0f,
		1.0f, 0.5f, 0.5f, 1.0f,
		1.0f, 0.5f, 0.5f, 1.0f,
		1.0f, 0.5f, 0.5f, 1.0f,
		1.0f, 0.5f, 0.5f, 1.0f,
		1.0f, 0.5f, 0.5f, 1.0f
	};
	VertexBuffer color(colors, 24);
	cgl(glEnableVertexAttribArray(COLOR_ATTRIB_LOC));
	cgl(glVertexAttribPointer(COLOR_ATTRIB_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0));


	IndexBuffer	ib(rawIndex, vectorInt.size());
	// IndexBuffer	ib(rawIndex, 6);

	std::string vertexShader = readFullFile("shaders/basic.vrt");
	std::string fragmentShader = readFullFile("shaders/basic.frg");
	unsigned int program = createShader(vertexShader, fragmentShader);

	cgl(glBindVertexArray(0));
	cgl(glUseProgram(0));
	cgl(glBindBuffer(GL_ARRAY_BUFFER, 0));
	cgl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	int	width = 0;
	int	height = 0;
	float r = 0.5f;
	// float increment = 0.05f;

	std::cout << "RENDERING STARTED" << std::endl;
	while(!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		cgl(glBindVertexArray(vao));
		cgl(glUseProgram(program));

		colors[1] = r;
		colors[4] = r;
		colors[6] = r;
		color.bind();
		cgl(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
		cgl(glEnableVertexAttribArray(COLOR_ATTRIB_LOC));
		cgl(glVertexAttribPointer(COLOR_ATTRIB_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0));

		ib.bind();

		cgl(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

		// if (r > 1.0f)
		// 	increment = -0.05f;
		// else if (r < 0.0f)
		// 	increment = 0.05f;
		// r += increment;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cgl(glDeleteProgram(program));
	cgl(glDeleteVertexArrays(1, &vao));
}

// static void drawTriangle(unsigned int shaderToUse, unsigned int vao, unsigned int vbo[NUM_BUFF], Vertex a, Vertex b, Vertex c, float baseColor)
// {
// 	cgl(glUseProgram(shaderToUse));
// 	cgl(glBindVertexArray(vao));

// 	float vertexes[9] = {
// 		a.x, a.y, a.z,
// 		b.x, b.y, b.z,
// 		c.x, c.y, c.z
// 	};

// 	float	colors[12] = {
// 		baseColor, baseColor, baseColor, 1.0f,
// 		baseColor, baseColor, baseColor, 1.0f,
// 		baseColor, baseColor, baseColor, 1.0f
// 	};

// 	cgl(glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION]));
// 	cgl(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW));
// 	cgl(glEnableVertexAttribArray(POSITION_ATTRIB_LOC));
// 	cgl(glVertexAttribPointer(POSITION_ATTRIB_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));

// 	cgl(glBindBuffer(GL_ARRAY_BUFFER, vbo[COLOR]));
// 	cgl(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
// 	cgl(glEnableVertexAttribArray(COLOR_ATTRIB_LOC));
// 	cgl(glVertexAttribPointer(COLOR_ATTRIB_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0));

// 	cgl(glDrawArrays(GL_TRIANGLES, 0, 3));
// }
