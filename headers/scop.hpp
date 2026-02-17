#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

#include "headers.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include "Object.hpp"
#include "Shader.hpp"
#include "Camera.hpp"


typedef	struct State {
	bool	autorotate;
	bool	textured;
	float	oldTime;
	bool	renderMode;
} State;

/**		MAIN		 **/


/**		INIT	 	 **/
GLFWwindow*	initWindow(int argc, char** argv, char** envp);


/**		CALLBACK	 **/
void	error_callback(int error, const char* description);
void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void	debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);


/**		SHADER		 **/
unsigned int	createShader(const std::string& vertexShader, const std::string& fragmentShader);


/**		UTILS		 **/
std::string	readFullFile(std::string path);
GLuint		loadBMP(const char* filepath);


void	keyPressHandler(GLFWwindow* window, Camera* camera, Object* obj, Shader* shader);
void	keyPress_PolygonMode(GLFWwindow* window, Shader* shader);
