#pragma once

#include "headers.hpp"

class Object {
	private:
		std::vector<Vertex>					_vertices;
		std::vector<std::vector<int>>		_faces;
		std::vector<std::vector<Vertex>>	_shapes;
		std::vector<std::vector<Vertex>>	_squares;
		
		void	_createShapes(void);
		void	_separateTrianglesSquares(void);
		void	_convertSquaresToTriangles(void);

	public:
		Object(void);
		Object(const Object& src);
		Object&	operator=(const Object& src);
		~Object(void);
		
		std::string	name;


		std::vector<std::vector<Vertex>>	triangles;
		unsigned int						fileCountFaces;
		unsigned int						_numTriangles;
		Mtl									mtl;

		void	createTriangles(std::vector<Vertex> vertices, std::vector<std::vector<int>> faces);
};
