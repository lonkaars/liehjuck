#pragma once
#include <math.h>
#include <string>
#include <vector>

// these stucts can be converted to classes if necessary
namespace jdscn
{

struct position {
	float x;
	float y;
	float z;
};

// typedef float[3] position;

struct position2D {
	int x;
	int y;
};

struct orientation {
	float x;
	float y;
	float z;
};

struct scale {
	float x;
	float y;
	float z;
};

// [0 -> 360]
typedef float angle;

struct color {
	int r;
	int g;
	int b;
	// int [0 -> 255]
};

// [0 -> 1]
typedef float percentage;

struct meta {
	std::string name;
};

struct material {
	struct color color;
	percentage roughness;
	percentage metallic;
	percentage transparency;
	struct meta meta;
};

class uv
{
	public:
	std::vector<position2D[3]> uv;
};

struct texture { // TODO: not yet implemented in the python plugin
	struct meta meta;
	std::string path;
	struct uv uv;
};

struct camera {
	struct position position;
	struct orientation orientation;
	struct meta meta;
	float focalLength;
};

struct light {
	std::string type;
	struct meta meta;
	struct orientation orientation;
	struct color color;
	struct position position;
	float power;
	float radius;
	angle cone;
};

struct object {
	struct orientation orientation;
	struct position position;
	struct scale scale;
	struct meta meta;
	struct material material;
	std::vector<struct position[3]> vertices;
	struct texture texture;
};

struct sceneMeta {
	std::string version;
	std::string generator;
};

struct scene {
	sceneMeta meta;
	struct camera camera;
	std::vector<light> lights;
	std::vector<object> objects;
};

}; // namespace jdscn
