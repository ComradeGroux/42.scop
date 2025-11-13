#include "scop.hpp"

std::vector<std::string>	split(std::string& str, const std::string& del)
{
	std::vector<std::string>	tokens;
	size_t						pos = 0;
	std::string					tok;

	while ((pos = str.find(del)) != std::string::npos)
	{
		tok = str.substr(0, pos);
		tokens.push_back(tok);
		str.erase(0, pos + del.length());
	}
	tokens.push_back(str);

	return tokens;
}

void	checkArgument(int argc, char *file)
{
	if(argc != 2)
		throw std::invalid_argument("Wrong number of argument");

	std::size_t found = std::string(file).find_last_of(".");
	if (strcmp(file + found, ".obj") != 0)
		throw std::invalid_argument("Wrong extension (must be .obj)");
}

std::ifstream	openFile(char *path)
{
	std::ifstream infile(path, std::ios::in);
	if (!infile.is_open())
		throw std::invalid_argument("File does not exist");
	return infile;
}

void	printVectorVectorString(std::vector<std::vector<std::string>> toPrint)
{
	size_t	length = toPrint.size();
	for (size_t i = 0; i < length; i++)
	{
		size_t	l = toPrint[i].size();
		for (size_t j = 0; j < l; j++)
			std::cout << toPrint[i][j] << " ";
		std::cout << std::endl;
	}
}
