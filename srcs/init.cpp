#include "scop.hpp"

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

Object initObjet()
{
	Object	obj;


	return obj;
}

void processObjFile(char *file, Object& obj)
{
	std::vector<Vertex>						pos_vertex;
	std::vector<std::vector<int>>			fac_vertex;
	std::string								materialFile;

	std::ifstream	infile = openFile(file);

	unsigned int	jFac = 0;
	std::string syntax_error = "Syntax error in ";
	syntax_error += file;
	for (std::string line; std::getline(infile, line);)
	{
		std::vector<std::string>	words = split(line, " ");
		int size = words.size();
		switch (hashit(words[0]))
		{
			case eComment:
				continue;

			case eVertex:
				if (size >= 4)
				{
					Vertex pos = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
					if (size == 5)
						pos.w = std::stof(words[4]);
					else if (size > 5)
						throw std::invalid_argument(syntax_error);
					pos.tX = pos.x;
					pos.tY = pos.y;
					pos.x /= pos.w;
					pos.y /= pos.w;
					pos.z /= pos.w;
					pos_vertex.push_back(pos);
				}
				else
					throw std::invalid_argument(syntax_error);
				continue;

			case eFaces:
				fac_vertex.push_back({});
				for (unsigned int i = 1; i < words.size(); i++)
					fac_vertex[jFac].push_back(std::stoi(words[i]));
				jFac++;
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

e_line_type	hashit(std::string const& inString)
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

