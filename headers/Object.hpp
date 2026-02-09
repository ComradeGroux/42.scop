#pragma once

#include <filesystem>
#include <vector>
#include <fstream>
#include <iostream>

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

class Object {
	private:
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

		std::vector<Vertex>						_vertices;			// List of vertex from obj files
		std::vector<std::vector<unsigned int>>	_faces;				// List of faces from obj files

		// List of shapes (vertexes that are members of multiples faces are duplicated)
		// This is absolutly not optimal nor performant. Will use an IndexBuffer to create faces by referencing each vertex
		std::vector<std::vector<Vertex>>		_shapes;
		// Contains only the squares from _shapes. This is not optimal too and will be replaced
		std::vector<std::vector<Vertex>>		_squares;


		void	_createTriangles(std::vector<Vertex> vertices, std::vector<std::vector<unsigned int>> faces);
		void	_createShapes(void);
		void	_separateTrianglesSquares(void);
		void	_convertSquaresToTriangles(void);

		void						_parseVertex(std::vector<Vertex>& pos, std::vector<std::string> line);
		void						_parseFaces(std::vector<std::vector<unsigned int>>& faces, std::vector<std::string> line, unsigned int& index);
		void						_parseMatLib(std::string file, std::string path);
		e_line_type					_hashit(std::string const& inString);
		std::ifstream				_openFile(char *path);
		std::vector<std::string>	_split(std::string& str, const std::string& del);



	public:
		std::vector<unsigned int>	_facesAllTriangles; // List of faces from obj files (squares are split in 2 triangles)


		Object(void);
		Object(const Object& src);
		Object&	operator=(const Object& src);
		~Object(void);
		
		int load(char *file);

		std::string	name;

		unsigned int						_numTriangles;

		std::vector<std::vector<Vertex>>	triangles;
		unsigned int						fileCountFaces;
		Mtl									mtl;


		inline std::vector<Vertex>						getVertices(void) const { return _vertices; }
		inline std::vector<std::vector<unsigned int>>	getFaces(void) const { return _faces; }
		inline int 										getNumberBaseTriangle(void) const { return triangles.size() - _squares.size(); }
};
