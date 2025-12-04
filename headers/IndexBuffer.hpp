#pragma once

#include "headers.hpp"

class IndexBuffer
{
	private:
		unsigned int	_rendererId;
		unsigned int	_count;

	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer(void);

		void	bind(void) const;
		void	unbind(void) const;

		unsigned int getCount(void) const;
};
