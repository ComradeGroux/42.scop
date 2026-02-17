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

GLuint loadBMP(const char* filepath)
{
	FILE* file = fopen(filepath, "rb");
	if (!file) {
		std::cerr << "Impossible d'ouvrir " << filepath << std::endl;
		return 0;
	}

	unsigned char	header[54];
	if (fread(header, 1, 54, file) != 54) {
		fclose(file);
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		fclose(file);
		return 0;
	}

	unsigned int	dataPos, width, height, imageSize;
	unsigned short	bitsPerPixel;
	memcpy(&dataPos,		&header[0x0A], 4);
	memcpy(&width,			&header[0x12], 4);
	memcpy(&height,			&header[0x16], 4);
	memcpy(&imageSize,		&header[0x22], 4);
	memcpy(&bitsPerPixel,	&header[0x1C], 2);

	if (bitsPerPixel != 24)
	{
		std::cerr << "BMP 32 bits detected" << std::endl;
		fclose(file);
		return 0;
	}
	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;

	unsigned char* data = new unsigned char[imageSize];

	fseek(file, dataPos, SEEK_SET);
	size_t t = fread(data, 1, imageSize, file);
	(void)t;
	fclose(file);

	for (unsigned int i = 0; i + 2 < imageSize; i += 3) {
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] data;
	return textureID;
}