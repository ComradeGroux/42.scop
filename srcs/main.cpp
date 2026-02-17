#include "Object.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include "scop.hpp"

static void	renderer(GLFWwindow* window, Object& obj);
static void	renderLoopIB(GLFWwindow* window, Shader* shader, VertexArray* va, IndexBuffer* ib, Object* obj, Camera* camera);


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

	Camera				camera;
	camera.setPosition(vec3(0.0f, 0.0f, 2.0f));
	renderLoopIB(window, &shader, &va, &ib, &obj, &camera);
}

static void	renderLoopIB(GLFWwindow* window, Shader* shader, VertexArray* va, IndexBuffer* ib, Object* obj, Camera* camera)
{
	int		width = 0;
	int		height = 0;

	State	state = { true, false, 0.0f, false };
	glfwSetWindowUserPointer(window, &state);

	GLuint	textureID = loadBMP("resources/cat.bmp");
	// shader->bind();
	shader->setTexture(textureID);

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		cgl(glViewport(0, 0, width, height));
		cgl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		keyPressHandler(window, camera, obj, shader);
		if (state.renderMode)
		{
			keyPress_PolygonMode(window, shader);
			state.renderMode = false;
		}
		shader->bind();

		if (state.autorotate)
		{
			float angle = glfwGetTime() - state.oldTime;
			mat4_rotate(obj->model, angle, 0.0f, 1.0f, 0.0f);
		}
		if (state.textured)
			shader->setUniform1i("textured", 1);
		else
			shader->setUniform1i("textured", 0);

		shader->setModel(obj->model);
		shader->setView(camera->getViewMatrix());
		shader->setPerspective(camera->getProjection(), 80.0f, 0.1f, 100.0f, width, height);

		va->bind();
		ib->bind();
		cgl(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

