#include "scop.hpp"

static std::string syntax_error = "Syntax error in ";
static e_line_type	hashit(std::string const& inString);
static void parseVertex(std::vector<Vertex>& pos, std::vector<std::string> line);
static void parseFaces(std::vector<std::vector<int>>& faces, std::vector<std::string> line, unsigned int& index);
static void parseMatLib(Object& obj, std::string file, std::string path);
static 		GLFWwindow*	createWindow();

static void	checkArgument(int argc, char *file)
{
	if(argc != 2)
		throw std::invalid_argument("Wrong number of argument");

	std::size_t found = std::string(file).find_last_of(".");
	if (strcmp(file + found, ".obj") != 0)
		throw std::invalid_argument("Wrong extension (must be .obj)");
}

GLFWwindow*	initWindow(int argc, char** argv, char** envp)
{
	GLFWwindow*	window;
	try
	{
		checkArgument(argc, argv[1]);

		window = createWindow();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return nullptr;
	}
	return window;
}

static GLFWwindow*	createWindow()
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

int loadObjet(char *file, Object& obj)
{
	std::vector<Vertex>						pos_vertex;
	std::vector<std::vector<int>>			fac_vertex;
	std::string								materialFile;

	std::ifstream	infile = openFile(file);

	unsigned int	countFaces = 0;
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
			case eVertexNormal:

				continue;
			case eVertexTexture:

				continue;
			case eFaces:
				parseFaces(fac_vertex, words, countFaces);
				continue;
			case eMatLib:
				materialFile = words[1];
				parseMatLib(obj, materialFile, file);
				continue;
			case eUseMatLib:
			case eName:
				obj.name = words[1];
			case eSmooth:
			case eDefault:
				continue;
			default:
				std::cerr << "Error: no case for \"" << words[0] << "\"" << std::endl;
				return -1;
				break;
		}
	}
	infile.close();

	obj.createTriangles(pos_vertex, fac_vertex);
	obj.fileCountFaces = countFaces;

	return 0;
}

static e_line_type	hashit(std::string const& inString)
{
	if (inString.empty())
		return eComment;
	if (inString == "#")
		return eComment;
	if (inString == "v")
		return eVertex;
	if (inString == "vn")
		return eVertexNormal;
	if (inString == "vt")
		return eVertexTexture;
	if (inString == "f")
		return eFaces;
	if (inString == "o")
		return eName;
	if (inString == "usemtl")
		return eUseMatLib;
	if (inString == "newmtl")
		return eNewMat;
	if (inString == "Ns")
		return eNs;
	if (inString == "Ka")
		return eKa;
	if (inString == "Kd")
		return eKd;
	if (inString == "Ks")
		return eKs;
	if (inString == "Ni")
		return eNi;
	if (inString == "d")
		return eD;
	if (inString == "illum")
		return eIllum;
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

static void parseMatLib(Object& obj, std::string file, std::string path)
{
	std::filesystem::path p = path;
	std::string realPath = p.parent_path();
	realPath += std::filesystem::path::preferred_separator + file;
	std::ifstream infile = openFile((char*)realPath.c_str());

	for (std::string line; std::getline(infile, line);)
	{
		std::vector<std::string>	words = split(line, " ");
		switch (hashit(words[0]))
		{
			case eComment:
				continue;
			case eNewMat:
				obj.mtl.name = words[1];
				continue;
			case eNs:
				obj.mtl.ns = std::stof(words[1]);
				continue;
			case eKa:
				obj.mtl.ka = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
				continue;
			case eKd:
				obj.mtl.kd = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
				continue;
			case eKs:
				obj.mtl.ks = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
				continue;
			case eNi:
				obj.mtl.ni = std::stof(words[1]);
				continue;
			case eD:
				obj.mtl.d = std::stof(words[1]);
				continue;
			case eIllum:
				obj.mtl.illum = std::stoi(words[1]);
				continue;

			default:
				continue;
		}
	}
}
