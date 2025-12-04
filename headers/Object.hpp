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

		inline std::vector<Vertex>				getVertices(void) const { return _vertices; }
		inline std::vector<std::vector<int>>	getFaces(void) const { return _faces; }
		inline int 								getNumberBaseTriangle(void) const { return triangles.size() - _squares.size(); }
};
