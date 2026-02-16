#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "glMath.hpp"
#include "opengl.hpp"

class Shader
{
	private:
		struct ShaderProgramSource {
			std::string	vertex;
			std::string	fragment;
		};

		std::string		_filepath;
		unsigned int	_rendererId;

		ShaderProgramSource	_parseShader(const std::string& filepath);
		unsigned int		_createShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int		_compileShader(unsigned int type, const std::string& source);


		int	_getUniformLocation(const std::string& name);

	public:
		Shader(const std::string& filepath);
		~Shader(void);

		enum e_render_mode {
			WIREFRAME,
			POINT,
			FILLED
		};

		void	bind(void) const;
		void	unbind(void) const;

		void	setRenderMode(e_render_mode mode);

		void	setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void	setUniform1f(const std::string& name, float v);
		void	setUniformMatrix4f(const std::string& name, mat4 v);
};
