#pragma once
#include "jdscn_types.h"
#include "win.h"
#include <array>
#include <math.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace jdscn
{

/**
 * @brief Information attached to all objects
 *
 * This class is used by every object to store it's name, but we might decide to add more properties to this class for debugging purposes.
 */
class Meta
{
	public:
	std::string name;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Meta, name);
};

/**
 * @brief Material used by objects
 *
 * This is a simplified version of the Principled BSDF shader in Blender.
 * Some of these properties might be removed due to implementation difficulties.
 */
class Material
{
	public:
	Color color;
	float roughness;
	float metallic;
	float transparency;
	Meta meta;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Material, color, roughness, metallic, transparency, meta);
};

class Texture
{ // TODO: not yet implemented in the python plugin
	public:
	Meta meta;
	std::string path;
	UV uv;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Texture, meta, path, uv);
};

class Camera
{
	public:
	Position position;
	Orientation orientation;
	Meta meta;
	float focalLength;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Camera, position, orientation, meta, focalLength);
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
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Light, type, meta, orientation, color, position, power, radius,
								   cone);
};

class Object
{
	public:
	Orientation orientation;
	Position position;
	Scale scale;
	Vertices vertices;
	Meta meta;
	Material material;
	void transform(std::function<jdscn::Position(jdscn::Position)>);
	void transformScale(jdscn::Scale, bool);
	void transformRotate(jdscn::Orientation, bool);
	void transformTranslate(jdscn::Position, bool);
	UVFloat projectVertices(Camera);
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Object, orientation, position, scale, vertices, meta, material);
	/* Texture texture; */
};

class SceneMeta
{
	public:
	std::string version;
	std::string generator;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneMeta, version, generator);
};

class Scene
{
	public:
	SceneMeta meta;
	Camera camera;
	std::vector<Light> lights;
	std::vector<Object> objects;
	void draw(Win::Canvas, int);
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Scene, meta, camera, lights, objects);
};

}; // namespace jdscn
