#include "scop.hpp"

#include "Object.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "opengl.hpp"
#include "glMath.hpp"

static void keyPress_PolygonMode(GLFWwindow* window, Shader* shader);

void	keyPressHandler(GLFWwindow* window, Camera* camera, Object* obj, Shader* shader)
{
	keyPress_PolygonMode(window, shader);
}

void keyPress_PolygonMode(GLFWwindow* window, Shader* shader)
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		shader->setRenderMode(Shader::FILLED);
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		shader->setRenderMode(Shader::WIREFRAME);
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		shader->setRenderMode(Shader::POINT);
}
