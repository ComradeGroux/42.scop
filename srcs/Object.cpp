#include "Object.hpp"

static std::string	syntax_error = "Syntax error in ";

Object::Object(void)
{
	fileCountFaces = 0;
	_numTriangles = 0;
	name = "";
	mat4_identity(model);
}

Object::Object(const Object& src)
{

}

Object& Object::operator=(const Object& src)
{
	return *this;
}

Object::~Object(void)
{

}

void	Object::_createTriangles(std::vector<Vertex> vertices, std::vector<std::vector<unsigned int>> faces)
{
	_vertices = vertices;
	_faces = faces;

	_createShapes();
	_separateTrianglesSquares();
	_convertSquaresToTriangles();
}

void	Object::_createShapes(void)
{
	for (unsigned int i = 0; i < _faces.size(); i++)
	{
		if (_faces[i].size() >= 3)
		{
			std::vector<Vertex> shape;
			if (_faces[i].size() == 4)
			{
				_facesAllTriangles.push_back(_faces[i][0]);
				_facesAllTriangles.push_back(_faces[i][1]);
				_facesAllTriangles.push_back(_faces[i][2]);

				_facesAllTriangles.push_back(_faces[i][0]);
				_facesAllTriangles.push_back(_faces[i][2]);
				_facesAllTriangles.push_back(_faces[i][3]);
			}
			else if (_faces[i].size() == 3)
			{
				_facesAllTriangles.push_back(_faces[i][0]);
				_facesAllTriangles.push_back(_faces[i][1]);
				_facesAllTriangles.push_back(_faces[i][2]);
			}
			else
				std::cerr << "faces not 4 or 3" << std::endl;


			for (unsigned int j = 0; j < _faces[i].size(); j++)
			{
				shape.push_back(_vertices[_faces[i][j]]);
			}
			_shapes.push_back(shape);
		}
		else
			throw std::invalid_argument("Invalid face with less than 3 indices encounter");
	}
}

void	Object::_separateTrianglesSquares(void)
{
	for (unsigned int i = 0; i < _shapes.size(); i++)
	{
		if (_shapes[i].size() == 3)
			triangles.push_back(_shapes[i]);
		else if (_shapes[i].size() == 4)
			_squares.push_back(_shapes[i]);
		else
			throw std::invalid_argument("Invalid shape detected !");
	}
}

void	Object::_convertSquaresToTriangles(void)
{
	for (unsigned int i = 0; i < _squares.size(); i++)
	{
		Vertex	a = _squares[i][0];
		Vertex	b = _squares[i][1];
		Vertex	c = _squares[i][2];
		Vertex	d = _squares[i][3];

		std::vector<Vertex>	t1 = { a, b, c };
		std::vector<Vertex>	t2 = { a, c, d };

		triangles.push_back(t1);
		triangles.push_back(t2);
	}
}

int Object::load(char *file)
{
	std::vector<Vertex>						pos_vertex;
	std::vector<std::vector<unsigned int>>	fac_vertex;
	std::string								materialFile;

	std::ifstream	infile = _openFile(file);

	

	unsigned int	countFaces = 0;
	syntax_error += file;
	for (std::string line; std::getline(infile, line);)
	{
		std::vector<std::string>	words = _split(line, " ");
		switch (_hashit(words[0]))
		{
			case eComment:
				continue;
			case eVertex:
				_parseVertex(pos_vertex, words);
				continue;
			case eVertexNormal:


				continue;
			case eVertexTexture:


				continue;
			case eFaces:
				_parseFaces(fac_vertex, words, countFaces);
				continue;
			case eMatLib:
				materialFile = words[1];
				_parseMatLib(materialFile, file);
				continue;
			case eUseMatLib:


			case eName:
				name = words[1];
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
	
	_createTriangles(pos_vertex, fac_vertex);

	_centerAndNormalize();

	fileCountFaces = countFaces;

	return 0;
}

Object::e_line_type	Object::_hashit(std::string const& inString)
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

void Object::_parseVertex(std::vector<Vertex>& pos, std::vector<std::string> line)
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

void Object::_parseFaces(std::vector<std::vector<unsigned int>>& faces, std::vector<std::string> line, unsigned int& index)
{
	faces.push_back({});
	for (unsigned int i = 1; i < line.size(); i++)
		faces[index].push_back(std::stoul(line[i]) - 1);
	index++;
}

void Object::_parseMatLib(std::string file, std::string path)
{
	std::filesystem::path p = path;
	std::string realPath = p.parent_path();
	realPath += std::filesystem::path::preferred_separator + file;
	std::ifstream infile = _openFile((char*)realPath.c_str());

	for (std::string line; std::getline(infile, line);)
	{
		std::vector<std::string>	words = _split(line, " ");
		switch (_hashit(words[0]))
		{
			case eComment:
				continue;
			case eNewMat:
				mtl.name = words[1];
				continue;
			case eNs:
				mtl.ns = std::stof(words[1]);
				continue;
			case eKa:
				mtl.ka = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
				continue;
			case eKd:
				mtl.kd = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
				continue;
			case eKs:
				mtl.ks = { std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) };
				continue;
			case eNi:
				mtl.ni = std::stof(words[1]);
				continue;
			case eD:
				mtl.d = std::stof(words[1]);
				continue;
			case eIllum:
				mtl.illum = std::stoi(words[1]);
				continue;
			default:
				continue;
		}
	}
}

std::vector<std::string>	Object::_split(std::string& str, const std::string& del)
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

std::ifstream	Object::_openFile(char *path)
{
	std::ifstream infile(path, std::ios::in);
	if (!infile.is_open())
		throw std::runtime_error("File does not exist");
	return infile;
}

Object::BoundingBox	Object::_calculateBoundingBox(void)
{
	BoundingBox box;

	float	minX = std::numeric_limits<float>::max();
	float	maxX = std::numeric_limits<float>::lowest();
	float	minY = std::numeric_limits<float>::max();
	float	maxY = std::numeric_limits<float>::lowest();
	float	minZ = std::numeric_limits<float>::max();
	float	maxZ = std::numeric_limits<float>::lowest();

	for (const auto& v : _vertices)
	{
		if (v.x < minX) minX = v.x;
		if (v.x > maxX) maxX = v.x;
		if (v.y < minY) minY = v.y;
		if (v.y > maxY) maxY = v.y;
		if (v.z < minZ) minZ = v.z;
		if (v.z > maxZ) maxZ = v.z;
	}

	box.centerX = (maxX + minX) / 2.0f;
	box.centerY = (maxY + minY) / 2.0f;
	box.centerZ = (maxZ + minZ) / 2.0f;

	box.sizeX = maxX - minX;
	box.sizeY = maxY - minY;
	box.sizeZ = maxZ - minZ;

	box.maxSize = box.sizeX;
	if (box.maxSize < box.sizeY)
		box.maxSize = box.sizeY;
	if (box.maxSize < box.sizeZ)
		box.maxSize = box.sizeZ;

	return box;
}

void	Object::_centerAndNormalize(void)
{
	BoundingBox	box = _calculateBoundingBox();

	for (auto& v : _vertices)
	{
		v.x -= box.centerX;
		v.y -= box.centerY;
		v.z -= box.centerZ;

		v.x /= (box.maxSize / NORMALIZE_TO);
		v.y /= (box.maxSize / NORMALIZE_TO);
		v.z /= (box.maxSize / NORMALIZE_TO);
	}
}
