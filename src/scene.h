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

typedef floatXYZ pos;
typedef floatXYZ scl;
typedef floatXYZ ort;

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
	std::vector<class position2D[3]> uv;
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
	pos position;
	typedef ort orientation;
	class meta meta;
	float focalLength;
};

class light
{
	public:
	std::string type;
	class meta meta;
	typedef ort orientation;
	class color color;
	typedef pos position;
	float power;
	float radius;
	float cone;
};

class object
{
	public:
	typedef ort orientation;
	typedef pos position;
	typedef scl scale;
	std::vector<pos[3]> vertices;
	class meta meta;
	class material material;
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
