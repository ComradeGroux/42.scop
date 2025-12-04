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

typedef struct t_Vertex {
	float x;
	float y;
	float z;
	float tX;
	float tY;
	float nX;
	float nY;
	float nZ;
	float w = 1.0;
} Vertex;
