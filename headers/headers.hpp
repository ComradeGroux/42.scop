#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

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

enum e_line_type {
	eDefault,
	eComment,
	eVertex,
	eVertexNormal,
	eVertexTexture,
	eFaces,
	eName,
	eMatLib,
	eUseMatLib,
	eNewMat,
	eNs,
	eKa,
	eKd,
	eKs,
	eNi,
	eD,
	eIllum,
	eSmooth
};

typedef struct t_Vertex {
	float x, y, z;
	float tX, tY;
	float nX, nY, nZ;
	float w = 1.0;
} Vertex;

struct Uv {
	float u, v, w;
};

struct Ka {
	float r, g, b;
};

struct Kd {
	float r, g, b;
};

struct Ks {
	float r, g, b;
};

struct Mtl
{
	Ka ka;
	Kd kd;
	Ks ks;
	float ns, ni, d;
	int illum;
	std::string name;
};
