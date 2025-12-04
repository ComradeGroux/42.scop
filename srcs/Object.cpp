#include "object.hpp"

#include "scop.hpp"


Object::Object(void)
{
	_numFaces = 0;
	_numTriangles = 0;
}

Object::Object(const Object& src)
{

}

Object& Object::operator=(const Object& src)
{
	return *this;
}

Object::~Object(void)
{

}

void	Object::createTriangles(std::vector<Vertex> vertices, std::vector<std::vector<int>> faces)
{
	_vertices = vertices;
	_faces = faces;
	
	_createShapes();
	_separateTrianglesSquares();
	_convertSquaresToTriangles();
}

void	Object::_createShapes(void)
{
	for (unsigned int i = 0; i < _faces.size(); i++)
	{
		if (_faces[i].size() >= 3)
		{
			std::vector<Vertex> shape;
			for (unsigned int j = 0; j < _faces[i].size(); j++)
				shape.push_back(_vertices[_faces[i][j]]);
			_shapes.push_back(shape);
		}
		else
			throw std::invalid_argument("Invalid face with less than 3 indices encounter");
	}
}

void	Object::_separateTrianglesSquares(void)
{
	for (unsigned int i = 0; i < _shapes.size(); i++)
	{
		if (_shapes[i].size() == 3)
			triangles.push_back(_shapes[i]);
		else if (_shapes[i].size() == 4)
			squares.push_back(_shapes[i]);
		else
			throw std::invalid_argument("Invalid shape detected !");
	}
}

void	Object::_convertSquaresToTriangles(void)
{
	for (unsigned int i = 0; i < squares.size(); i++)
	{

	}
}
