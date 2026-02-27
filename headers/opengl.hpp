#pragma once

#include "glad.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define cgl(x) GLClearError(); x; GLGetError(#x, __FILE__, __LINE__)

void	GLClearError();
void	GLGetError(const char *function, const char *file, int line);
