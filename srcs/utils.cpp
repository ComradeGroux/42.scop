#include "scop.hpp"

static std::ifstream	openFile(char *path)
{
	std::ifstream infile(path, std::ios::in);
	if (!infile.is_open())
		throw std::runtime_error("File does not exist");
	return infile;
}

std::string	readFullFile(std::string path)
{
	try
	{
		std::ifstream	infile = openFile((char*)path.c_str());

		std::string		content;
		content.resize(std::filesystem::file_size(path));
		infile.read(content.data(), content.size());

		return content;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return std::string();
	}
}

void	GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

void GLGetError(const char *function, const char *file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << ") in " << function << " " << file << " at line " << line << std::endl;
	}
}
