#include "scop.hpp"

static unsigned int compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char*	msg = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, msg);
		std::cerr << "Error: Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cerr << msg;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

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
