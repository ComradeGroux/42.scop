#pragma once

#include "headers.hpp"
#include "object.hpp"

/**		MAIN		 **/
void drawTriangle(unsigned int shaderToUse, unsigned int vao, unsigned int vbo[NUM_BUFF], Vertex a, Vertex b, Vertex c, float baseColor);
void drawSquare(unsigned int shaderToUse, unsigned int vao, unsigned int vbo[NUM_BUFF], Vertex a, Vertex b, Vertex c, Vertex d, float baseColor);


/**		INIT	 	 **/
void						checkArgument(int argc, char *file);
GLFWwindow*					initWindow();
void 						processObjFile(char *file, Object& obj);
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
