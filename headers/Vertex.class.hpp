#pragma once

#include "Position.class.hpp"

class Vertex {
	private:
		Position	_pos;

	public:
		Vertex(void);
		Vertex(const Vertex& src);
		Vertex& operator=(const Vertex& src);
		~Vertex(void);
};
