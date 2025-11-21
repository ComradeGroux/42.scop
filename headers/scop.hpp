#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "glad.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#ifndef WIDTH
# define WIDTH 640
#endif
#ifndef HEIGHT
# define HEIGHT 480
#endif

/**		INIT	 	 **/
void						checkArgument(int argc, char *file);
GLFWwindow*					initWindow();


/**		CALLBACK	 **/
void	error_callback(int error, const char* description);
void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


/**		SHADER		 **/
int		createShader(const std::string& vertexShader, const std::string& fragmentShader);


/**		UTILS		 **/
std::vector<std::string>	split(std::string& str, const std::string& del);
void						printVectorVectorString(std::vector<std::vector<std::string>> toPrint);
std::ifstream				openFile(char *path);
