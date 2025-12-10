#pragma once

#include "headers.hpp"

class VertexBuffer
{
	private:
		unsigned int	_rendererId;

	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer(void);

		void	bind(void) const;
		void	unbind(void) const;
};
