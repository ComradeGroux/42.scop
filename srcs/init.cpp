#include "scop.hpp"

static e_line_type	hashit(std::string const& inString);
static std::string syntax_error = "Syntax error in ";
static void parseVertex(std::vector<Vertex>& pos, std::vector<std::string> line);
static void parseFaces(std::vector<std::vector<int>>& faces, std::vector<std::string> line, unsigned int& index);


void	checkArgument(int argc, char *file)
{
	if(argc != 2)
		throw std::invalid_argument("Wrong number of argument");

	std::size_t found = std::string(file).find_last_of(".");
	if (strcmp(file + found, ".obj") != 0)
		throw std::invalid_argument("Wrong extension (must be .obj)");
}

GLFWwindow*	initWindow()
{
	if(glfwInit() != GLFW_TRUE)
		throw std::runtime_error("GLFW init goes wrong");
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	GLFWwindow*	window = glfwCreateWindow(WIDTH, HEIGHT, "scop", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		throw std::runtime_error("The window's creation failed");
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		throw std::runtime_error("An issue occured during the loading of GLAD");
	}

	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(debug_callback, nullptr);

	return window;
}

void initObjet(char *file, Object& obj)
{
	std::vector<Vertex>						pos_vertex;
	std::vector<std::vector<int>>			fac_vertex;
	std::string								materialFile;

	std::ifstream	infile = openFile(file);

	unsigned int	numFaces = 0;
	syntax_error += file;
	for (std::string line; std::getline(infile, line);)
	{
		std::vector<std::string>	words = split(line, " ");
		switch (hashit(words[0]))
		{
			case eComment:
				continue;

			case eVertex:
				parseVertex(pos_vertex, words);
				continue;

			case eFaces:
				parseFaces(fac_vertex, words, numFaces);
				continue;

			case eMatLib:
				materialFile = words[1];
				continue;

			case eUseMatLib:
			case eName:
			case eSmooth:
			case eDefault:
				continue;
			default:
				std::cerr << "Error: no case for \"" << words[0] << "\"" << std::endl;
				break;
		}
	}
	infile.close();

	obj.createTriangles(pos_vertex, fac_vertex);
}

static e_line_type	hashit(std::string const& inString)
{
	if (inString == "#")
		return eComment;
	if (inString == "v")
		return eVertex;
	if (inString == "f")
		return eFaces;
	if (inString.empty())
		return eComment;
	if (inString == "o")
		return eName;
	if (inString == "usemtl")
		return eUseMatLib;
	if (inString == "mtllib")
		return eMatLib;
	if (inString == "s")
		return eSmooth;

	return eDefault;
}

static void parseVertex(std::vector<Vertex>& pos, std::vector<std::string> line)
{
	if (line.size() >= 4)
	{
		Vertex tmp = { std::stof(line[1]), std::stof(line[2]), std::stof(line[3]) };
		if (line.size() == 5)
			tmp.w = std::stof(line[4]);
		else if (line.size() > 5)
			throw std::invalid_argument(syntax_error);
		tmp.tX = tmp.x;
		tmp.tY = tmp.y;
		tmp.x /= tmp.w;
		tmp.y /= tmp.w;
		tmp.z /= tmp.w;
		pos.push_back(tmp);
	}
	else
		throw std::invalid_argument(syntax_error);
}

static void parseFaces(std::vector<std::vector<int>>& faces, std::vector<std::string> line, unsigned int& index)
{
	faces.push_back({});
	for (unsigned int i = 1; i < line.size(); i++)
		faces[index].push_back(std::stoi(line[i]));
	index++;
}
