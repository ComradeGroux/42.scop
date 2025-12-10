#pragma once

#include <vector>
#include <cassert>

#include "opengl.hpp"

struct VertexArrayElement {
	unsigned int	type;
	unsigned int	count;
	unsigned char	normalized;

	static unsigned int getSizeType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_INT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		assert(false);
		return 0;
	}
};

class VertexBufferLayout
{
	private:
		std::vector<VertexArrayElement>	_elements;
		unsigned int					_stride;

	public:
		VertexBufferLayout(void);
		~VertexBufferLayout(void);

		std::vector<VertexArrayElement>	getElements(void) const;
		unsigned int					getStride(void) const;

		template<typename T>
		void push(unsigned int count);
};
