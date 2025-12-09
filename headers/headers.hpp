#pragma once

#include <cstring>

#include "opengl.hpp"

#ifndef WIDTH
# define WIDTH 640
#endif
#ifndef HEIGHT
# define HEIGHT 480
#endif

#define POSITION_ATTRIB_LOC 0
#define COLOR_ATTRIB_LOC 1
enum { POSITION, COLOR, NUM_BUFF };
