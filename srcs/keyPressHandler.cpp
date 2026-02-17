#include "scop.hpp"

#include "Object.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "opengl.hpp"
#include "glMath.hpp"

static	void	keyPress_MoveObject(GLFWwindow* window, Object* obj);

void	keyPressHandler(GLFWwindow* window, Camera* camera, Object* obj, Shader* shader)
{
	keyPress_MoveObject(window, obj);
}

void	keyPress_PolygonMode(GLFWwindow* window, Shader* shader)
{
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		switch (shader->getRenderMode())
		{
			case Shader::FILLED:
			shader->setRenderMode(Shader::WIREFRAME);
			break;

			case Shader::WIREFRAME:
			shader->setRenderMode(Shader::POINT);
			break;

			default:
			shader->setRenderMode(Shader::FILLED);
			break;
		}
	}
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
