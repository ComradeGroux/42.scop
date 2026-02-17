#include "scop.hpp"

#include "Object.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "opengl.hpp"
#include "glMath.hpp"

static	void	keyPress_PolygonMode(GLFWwindow* window, Shader* shader);
static	void	keyPress_MoveObject(GLFWwindow* window, Object* obj);

void	keyPressHandler(GLFWwindow* window, Camera* camera, Object* obj, Shader* shader)
{
	keyPress_PolygonMode(window, shader);
	keyPress_MoveObject(window, obj);
}

void	keyPress_PolygonMode(GLFWwindow* window, Shader* shader)
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		shader->setRenderMode(Shader::FILLED);
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		shader->setRenderMode(Shader::WIREFRAME);
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		shader->setRenderMode(Shader::POINT);
}

void	keyPress_MoveObject(GLFWwindow* window, Object* obj)
{
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
	{
		mat4_move(obj->model, 0.0f, 0.05f, 0.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
	{
		mat4_move(obj->model, 0.0f, -0.05f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mat4_move(obj->model, 0.0f, 0.0f, -0.05f);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mat4_move(obj->model, 0.0f, 0.0f, 0.05f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		mat4_move(obj->model, -0.05f, 0.0f, 0.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		mat4_move(obj->model, 0.05f, 0.0f, 0.0f);
	}
}
