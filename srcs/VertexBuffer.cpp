#include "VertexBuffer.hpp"
#include "opengl.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	cgl(glGenBuffers(1, &_rendererId));
	cgl(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
	cgl(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	cgl(glDeleteBuffers(1, &_rendererId));
}

void	VertexBuffer::bind(void) const
{
	cgl(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
}

void	VertexBuffer::unbind(void) const
{
	cgl(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
