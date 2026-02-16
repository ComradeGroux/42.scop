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

	Shader	shader("shaders/basic.shader");

	va.unbind();
	shader.unbind();
	vb.unbind();
	ib.unbind();

	renderLoopIB(window, &shader, &va, &ib);
}

static void	renderLoopIB(GLFWwindow* window, Shader* shader, VertexArray* va, IndexBuffer* ib)
{
	int	width = 0;
	int	height = 0;

	mat4	model;
	mat4_identity(model);
	mat4	view;
	mat4	projection;


	float angle = 0.0;
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		angle = glfwGetTime();
		mat4_rotate(model, angle, 0.0f, 1.0f, 0.0f);
		mat4_look_at(view, vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		mat4_perspective(projection, deg_to_radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		shader->bind();
		shader->setUniformMatrix4f("model", model);
		shader->setUniformMatrix4f("view", view);
		shader->setUniformMatrix4f("projection", projection);

		va->bind();
		ib->bind();
		cgl(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

