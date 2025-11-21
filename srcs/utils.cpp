#include "scop.hpp"

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

std::ifstream	openFile(char *path)
{
	std::ifstream infile(path, std::ios::in);
	if (!infile.is_open())
		throw std::runtime_error("File does not exist");
	return infile;
}

std::string	readFullFile(char *path)
{
	try
	{
		std::ifstream	infile = openFile(path);

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
