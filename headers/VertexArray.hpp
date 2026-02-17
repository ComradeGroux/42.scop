#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
	private:
		unsigned int	_rendererId;

	public:
		VertexArray(void);
		~VertexArray(void);

		void	bind(void) const;
		void	unbind(void) const;

		void	addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
