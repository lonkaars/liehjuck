#pragma once
#include <math.h>
#include <string>
#include <vector>

// these stucts can be converted to classes if necessary
namespace jdscn
{

class floatXYZ {
	public:
	float x;
	float y;
	float z;
};

class scale : public floatXYZ {};
class position : public floatXYZ {};
class orientation : public floatXYZ {};

class position2D
{
	public:
	int x;
	int y;
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
	class color color;
	float roughness;
	float metallic;
	float transparency;
	class meta meta;
};

class uv
{
	public:
	std::vector<position2D[3]> uv;
};

class texture
{ // TODO: not yet implemented in the python plugin
	public:
	class meta meta;
	std::string path;
	class uv uv;
};

class camera
{
	public:
	class position position;
	class orientation orientation;
	class meta meta;
	float focalLength;
};

class light
{
	public:
	std::string type;
	class meta meta;
	class orientation orientation;
	class color color;
	class position position;
	float power;
	float radius;
	float cone;
};

class object
{
	public:
	class orientation orientation;
	class position position;
	class scale scale;
	class meta meta;
	class material material;
	std::vector<class position[3]> vertices;
	class texture texture;
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
	class sceneMeta meta;
	class camera camera;
	std::vector<light> lights;
	std::vector<object> objects;
};

}; // namespace jdscn
