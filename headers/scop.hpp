#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

/**		INIT	 **/
std::vector<std::string>	split(std::string& str, const std::string& del);
void						checkArgument(int argc, char *file);
std::ifstream				openFile(char *path);
void						printVectorVectorString(std::vector<std::vector<std::string>> toPrint);


/**		CALLBACK	 **/
void	error_callback(int error, const char* description);
void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
