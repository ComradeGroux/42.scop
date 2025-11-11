#include "Position.class.hpp"

Position::Position(void)
{

}

Position::Position(float x, float y, float z)
{
	_w = 1.0
	_x = x / _w;
	_y = y / _w;
	_z = z / _w;
}

Position::Position(float x, float y, float z, float w)
{
	_w = _w;
	_x = x / _w;
	_y = y / _w;
	_z = z / _w;
}

Position::Position(const Position& src)
{
	_x = src._x;
	_y = src._y;
	_z = src._z;
	_w = src._w;
}

Position&   Position::operator=(const Position& src)
{
	_x = src._x;
	_y = src._y;
	_z = src._z;
	_w = src._w;

	return *this;
}

Position::~Position(void)
{

}

float	Position::getX(void) const
{
	return _x;
}

void	Position::setX(float x)
{
	_x = x;
}

float	Position::getY(void) const
{
	return _y;
}

void	Position::setY(float y)
{
	_y = y;
}

float	Position::getZ(void) const
{
	return _z;
}

void	Position::setZ(float z)
{
	_z = z;
}
