#pragma once

#include "glMath.hpp"
#include "opengl.hpp"

class Camera {
	private:
		vec3	_position;
		vec3	_front;
		vec3	_up;
		mat4	_projection;
		mat4	_viewMatrix;

	public:
		Camera(void);
		Camera(const Camera& src);
		Camera& operator=(const Camera& src);
		~Camera(void);

		mat4&	getViewMatrix(void);
		mat4&	getProjection(void) { return _projection; };

		void	setPosition(vec3 position);
};
