#include "IndexBuffer.hpp"
#include "opengl.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	cgl(glGenBuffers(1, &_rendererId));
	cgl(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
	cgl(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	cgl(glDeleteBuffers(1, &_rendererId));
}

void	IndexBuffer::bind(void) const
{
	cgl(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
}

void	IndexBuffer::unbind(void) const
{
	cgl(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

unsigned int	IndexBuffer::getCount(void) const
{
	return _count;
}
