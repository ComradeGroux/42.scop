#pragma once

#include "headers.hpp"

class Object {
	private:
		std::vector<Vertex>					_vertices;
		std::vector<std::vector<Vertex>>	_shapes;
		
		void	_createShapes(void);
		void	_separateTrianglesSquares(void);
		void	_convertSquaresToTriangles(void);

	public:
		Object(void);
		Object(const Object& src);
		Object&	operator=(const Object& src);
		~Object(void);
		
		std::vector<std::vector<int>>		_faces;
		std::vector<std::vector<Vertex>>	triangles;
		std::vector<std::vector<Vertex>>	squares;
		unsigned int						_numFaces;
		unsigned int						_numTriangles;

		void	createTriangles(std::vector<Vertex> vertices, std::vector<std::vector<int>> faces);
};
