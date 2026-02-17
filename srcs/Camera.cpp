#include "Camera.hpp"

Camera::Camera(void)
{
	_up = vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(const Camera& src)
{
	_position = src._position;
	_front = src._front;
	_up = src._up;
}

Camera&	Camera::operator=(const Camera& src)
{
	_position = src._position;
	_front = src._front;
	_up = src._up;

	return *this;
}

Camera::~Camera(void)
{
}

mat4&	Camera::getViewMatrix(void)
{
	mat4_look_at(_viewMatrix, _position, _front, _up);
	return _viewMatrix;
}

void	Camera::setPosition(vec3 position)
{
	_position = position;
}

