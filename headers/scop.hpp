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

#define cgl(x) GLClearError(); x; GLGetError(#x, __FILE__, __LINE__)

#define POSITION_ATTRIB_LOC 0
#define COLOR_ATTRIB_LOC 1
enum { POSITION, COLOR, NUM_BUFF };

enum e_line_type {
	eDefault,
	eComment,
	eVertex,
	eFaces,
	eName,
	eMatLib,
	eUseMatLib,
	eSmooth
};

typedef struct t_Vec3 {
	float x;
	float y;
	float z;
	float w = 1.0;
} Vec3;


/**		INIT	 	 **/
void						checkArgument(int argc, char *file);
GLFWwindow*					initWindow();
e_line_type					hashit(std::string const& inString);


/**		CALLBACK	 **/
void						error_callback(int error, const char* description);
void						key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void						debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);


/**		SHADER		 **/
unsigned int				createShader(const std::string& vertexShader, const std::string& fragmentShader);


/**		UTILS		 **/
std::vector<std::string>	split(std::string& str, const std::string& del);
void						printVectorVectorString(std::vector<std::vector<std::string>> toPrint);
std::ifstream				openFile(char *path);
std::string					readFullFile(std::string path);
void						GLClearError();
void						GLGetError(const char *function, const char *file, int line);
