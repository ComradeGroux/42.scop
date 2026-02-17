#include "scop.hpp"

void	error_callback(int error, const char* description)
{
	std::cerr << "Error " << error << ": " << description << std::endl;
}

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	State* state = static_cast<State*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (state->autorotate)
			state->oldTime = glfwGetTime() - state->oldTime;
		else
			state->oldTime = glfwGetTime() - state->oldTime;
		state->autorotate = !(state->autorotate);
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		state->textured = !(state->textured);
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		state->renderMode = true;
}

void	debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	std::cerr << "OpenGL ERROR: " << message << std::endl;
}
