#include "VertexArray.hpp"

VertexArray::VertexArray(void)
{
	cgl(glGenVertexArrays(1, &_rendererId));
}

VertexArray::~VertexArray(void)
{
	cgl(glDeleteVertexArrays(1, &_rendererId));
}

void	VertexArray::bind(void) const
{
	cgl(glBindVertexArray(_rendererId));
}

void	VertexArray::unbind(void) const
{
	cgl(glBindVertexArray(0));
}

void	VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();

	std::vector<VertexArrayElement> elements = layout.getElements();
	size_t	offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		VertexArrayElement element = elements[i];
		cgl(glEnableVertexAttribArray(i));
		cgl(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<const void*>(offset)));
		offset += element.count * VertexArrayElement::getSizeType(element.type);
	}
}
