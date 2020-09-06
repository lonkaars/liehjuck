#pragma once
#include <math.h>
#include <string>
#include <vector>

// these stucts can be converted to classes if necessary
namespace jdscn
{

class FloatXYZ {
	public:
	float x;
	float y;
	float z;
};

typedef FloatXYZ Position;
typedef FloatXYZ Scale;
typedef FloatXYZ Orientation;

class Position2D
{
	public:
	int x;
	int y;
};

class Color
{
	public:
	int r;
	int g;
	int b;
	// int [0 -> 255]
};

class Meta
{
	public:
	std::string name;
};

class Material
{
	public:
	Color color;
	float roughness;
	float metallic;
	float transparency;
	Meta meta;
};

class UV
{
	public:
	std::vector<Position2D[3]> uv;
};

class Texture
{ // TODO: not yet implemented in the python plugin
	public:
	Meta meta;
	std::string path;
	UV uv;
};

class Camera
{
	public:
	Position position;
	Orientation orientation;
	Meta meta;
	float focalLength;
};

class Light
{
	public:
	std::string type;
	Meta meta;
	Orientation orientation;
	Color color;
	Position position;
	float power;
	float radius;
	float cone;
};

class Object
{
	public:
	Orientation orientation;
	Position position;
	Scale scale;
	std::vector<Position[3]> vertices;
	Meta meta;
	Material material;
	Texture texture;
};

class SceneMeta
{
	public:
	std::string version;
	std::string generator;
};

class Scene
{
	public:
	SceneMeta meta;
	Camera camera;
	std::vector<Light> lights;
	std::vector<Object> objects;
};

}; // namespace jdscn
