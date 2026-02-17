#include "Shader.hpp"

Shader::Shader(const std::string& filepath) : _filepath(filepath), _rendererId(0)
{
	ShaderProgramSource	src = _parseShader(filepath);
	_rendererId = _createShader(src.vertex, src.fragment);
	setRenderMode(Shader::FILLED);
}

Shader::~Shader(void)
{
	cgl(glDeleteProgram(_rendererId));
}

void	Shader::bind(void) const
{
	cgl(glUseProgram(_rendererId));
}

void	Shader::unbind(void) const
{
	cgl(glUseProgram(0));
}

void	Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	cgl(glUniform4f(_getUniformLocation(name), v0, v1, v2, v3));
}

void	Shader::setUniform1f(const std::string& name, float v)
{
	cgl(glUniform1f(_getUniformLocation(name), v));
}

void	Shader::setUniform1i(const std::string& name, int v)
{
	cgl(glUniform1i(_getUniformLocation(name), v));
}

void	Shader::setUniformMatrix4f(const std::string& name, mat4 v)
{
	cgl(glUniformMatrix4fv(_getUniformLocation(name), 1, GL_FALSE, v));
}

int	Shader::_getUniformLocation(const std::string& name)
{
	cgl(int location = glGetUniformLocation(_rendererId, name.c_str()));
	if (location == -1)
		std::cerr << "Warning: uniform " << name << " doesn't exist !" << std::endl;
	return location;
}

Shader::ShaderProgramSource	Shader::_parseShader(const std::string& filepath)
{
	std::ifstream	stream(filepath);

	enum ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string			line;
	std::stringstream	ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int	Shader::_createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = _compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = _compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int	success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "Error: Program linking failed:\n" << infoLog << std::endl;

		glDeleteShader(vs);
		glDeleteShader(fs);

		return 0;
	}
	return program;
}

unsigned int	Shader::_compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	cgl(glShaderSource(id, 1, &src, nullptr));
	cgl(glCompileShader(id));

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len;
		cgl(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
		char*	msg = (char*)alloca(len * sizeof(char));
		cgl(glGetShaderInfoLog(id, len, &len, msg));
		std::cerr << "Error: Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cerr << msg;
		cgl(glDeleteShader(id));
		return 0;
	}

	return id;
}

void	Shader::setTexture(GLuint textureID)
{
	cgl(glActiveTexture(GL_TEXTURE0 + textureID));
	cgl(glBindTexture(GL_TEXTURE_2D, textureID));
	setUniform1i("textureSampler", textureID);
}

void	Shader::setModel(mat4 model)
{
	setUniformMatrix4f("model", model);
}

void	Shader::setView(mat4 view)
{
	setUniformMatrix4f("view", view);
}

void	Shader::setPerspective(mat4 projection, float fov_degree, float near, float far, int window_width, int window_height)
{
	mat4_perspective(projection, deg_to_radians(fov_degree), (float)window_width / (float)window_height, near, far);
	setUniformMatrix4f("projection", projection);
}

void	Shader::setRenderMode(e_render_mode mode)
{
	if (mode == WIREFRAME)
	{
		cgl(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		_actualRenderMode = Shader::WIREFRAME;
	}
	else if (mode == POINT)
	{
		cgl(glPolygonMode(GL_FRONT_AND_BACK, GL_POINT));
		_actualRenderMode = Shader::POINT;
	}
	else
	{
		cgl(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		_actualRenderMode = Shader::FILLED;
	}
}

Shader::e_render_mode	Shader::getRenderMode(void) const
{
	return _actualRenderMode;
}
