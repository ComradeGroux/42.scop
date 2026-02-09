#include "Object.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

#include "scop.hpp"

static void	renderer(GLFWwindow* window, Object& obj);
static void	renderLoopIB(GLFWwindow* window, Shader* shader, VertexArray* va, IndexBuffer* ib);

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
	VertexArray			va;
	std::vector<float>	vFloat;
	std::vector<Vertex> vertices = obj.getVertices();
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vFloat.push_back(vertices[i].x);
		vFloat.push_back(vertices[i].y);
		vFloat.push_back(vertices[i].z);
	}
	VertexBuffer		vb(vFloat.data(), vFloat.size() * sizeof(float));
	VertexBufferLayout	layout;
	layout.push<float>(3);
	va.addBuffer(vb, layout);
	IndexBuffer		ib(obj._facesAllTriangles.data(), obj._facesAllTriangles.size());

	// float rawPos[3 * 6] = {
	// 	-1.0f, -0.75f,	0.0f,
	// 	 0.0f, -0.75f,	0.0f,
	// 	 1.0f, -0.75f,	0.0f,
	// 	-0.5f,	0.0f,	0.0f,
	// 	 0.5f,	0.0f,	0.0f,
	// 	 0.0f,	0.75f,	0.0f
	// };
	// unsigned int rawIndex[9] = {
	// 	0, 1, 3,
	// 	1, 2, 4,
	// 	3, 4, 5
	// };
	// VertexArray			va;
	// VertexBuffer		vb(rawPos, sizeof(rawPos));
	// VertexBufferLayout	layout;
	// layout.push<float>(3);
	// va.addBuffer(vb, layout);
	// IndexBuffer	ib(rawIndex, (sizeof(rawIndex) / sizeof(unsigned int)));

	Shader	shader("shaders/basic.shader");

	va.unbind();
	shader.unbind();
	vb.unbind();
	ib.unbind();

	for (unsigned int i = 0; i < obj._facesAllTriangles.size(); i++)
	{
		std::cout << obj._facesAllTriangles[i] << " ";
		if (i % 3 == 2)
			std::cout << std::endl;
	}

	std::cout << "total triangles " << ib.getCount() / 3 << "\ttotal faces points " << ib.getCount() << std::endl;
	renderLoopIB(window, &shader, &va, &ib);
}

void	renderLoopIB(GLFWwindow* window, Shader* shader, VertexArray* va, IndexBuffer* ib)
{
	std::cout << "Rendering loop started" << std::endl;

	int	width = 0;
	int	height = 0;
	float r = 0.5f;
	float inc = 0.02f;

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		shader->bind();
		shader->setUniform4f("u_color", r, 0.0f, r, 0.0f);

		va->bind();
		ib->bind();
		cgl(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f)
			inc = -0.02f;
		else if (r < 0.1f)
			inc = 0.02f;
		r += inc;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void	renderLoopClassic(GLFWwindow *window, Shader* shader)
{
	std::cout << "Rendering loop started" << std::endl;

	int	width = 0;
	int	height = 0;
	float r = 0.5f;
	float inc = 0.02f;

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


		if (r > 1.0f)
			inc = -0.02f;
		else if (r < 0.1f)
			inc = 0.02f;
		r += inc;
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
