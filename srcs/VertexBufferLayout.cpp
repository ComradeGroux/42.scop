#include "VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout(void) : _stride(0)
{

}

VertexBufferLayout::~VertexBufferLayout(void)
{

}

std::vector<VertexArrayElement>	VertexBufferLayout::getElements(void) const
{
	return _elements;
}

unsigned int	VertexBufferLayout::getStride(void) const
{
	return _stride;
}

template<typename T>
void	VertexBufferLayout::push(unsigned int count)
{
	static_assert(false);
}

template<>
void	VertexBufferLayout::push<float>(unsigned int count)
{
	_elements.push_back({GL_FLOAT, count, GL_FALSE});
	_stride += VertexArrayElement::getSizeType(GL_FLOAT) * count;
}

template<>
void	VertexBufferLayout::push<unsigned int>(unsigned int count)
{
	_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	_stride += VertexArrayElement::getSizeType(GL_UNSIGNED_INT) * count;
}

template<>
void	VertexBufferLayout::push<int>(unsigned int count)
{
	_elements.push_back({GL_INT, count, GL_FALSE});
	_stride += VertexArrayElement::getSizeType(GL_INT) * count;
}

template<>
void	VertexBufferLayout::push<unsigned char>(unsigned int count)
{
	_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	_stride += VertexArrayElement::getSizeType(GL_UNSIGNED_BYTE) * count;
}
