#include "Object.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

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
	float rawPos[12] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	unsigned int rawIndex[6] = {
		0, 1, 2,
		0, 2, 3
	};

	VertexArray			va;
	VertexBuffer		vb(rawPos, 4 * 3 * sizeof(float));
	VertexBufferLayout	layout;
	layout.push<float>(3);
	va.addBuffer(vb, layout);

	IndexBuffer	ib(rawIndex, 6);

	Shader	shader("shaders/basic.shader");

	va.unbind();
	shader.unbind();
	vb.unbind();
	ib.unbind();

	int	width = 0;
	int	height = 0;

	std::cout << "RENDERING STARTED" << std::endl;
	while(!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		shader.bind();

		va.bind();
		ib.bind();
		cgl(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
