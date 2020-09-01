#pragma once
#include <math.h>
#include <string>
#include <vector>

// these stucts can be converted to classes if necessary
namespace jdscn
{

class position
{
	public:
	float x;
	float y;
	float z;
};

// typedef float[3] position;

class position2D
{
	public:
	int x;
	int y;
};

class orientation
{
	public:
	float x;
	float y;
	float z;
};

class scale
{
	public:
	float x;
	float y;
	float z;
};

class color
{
	public:
	int r;
	int g;
	int b;
	// int [0 -> 255]
};

class meta
{
	public:
	std::string name;
};

class material
{
	public:
	struct color color;
	float roughness;
	float metallic;
	float transparency;
	struct meta meta;
};

class uv
{
	public:
	std::vector<position2D[3]> uv;
};

class texture
{ // TODO: not yet implemented in the python plugin
	public:
	struct meta meta;
	std::string path;
	struct uv uv;
};

class camera
{
	public:
	struct position position;
	struct orientation orientation;
	struct meta meta;
	float focalLength;
};

class light
{
	public:
	std::string type;
	struct meta meta;
	struct orientation orientation;
	struct color color;
	struct position position;
	float power;
	float radius;
	float cone;
};

class object
{
	public:
	struct orientation orientation;
	struct position position;
	struct scale scale;
	struct meta meta;
	struct material material;
	std::vector<struct position[3]> vertices;
	struct texture texture;
};

class sceneMeta
{
	public:
	std::string version;
	std::string generator;
};

class scene
{
	public:
	sceneMeta meta;
	struct camera camera;
	std::vector<light> lights;
	std::vector<object> objects;
};

}; // namespace jdscn
