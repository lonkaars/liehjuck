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
 * This class is used by every object to store properties that aren't rendered. We might decide to
 * add more properties to this class for debugging purposes.
 */
class Meta
{
	public:
	std::string name;
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Meta, name);
	/** @endcond */
};

/**
 * @brief Used by objects
 *
 * This is a simplified version of the Principled BSDF shader in Blender.
 * Some of these properties might be removed due to implementation difficulties.
 */
class Material
{
	public:
	Color color;
	/** @brief Reflection blurryness */
	float roughness;
	/** @brief Defines how much of the material's color you can see in the reflections */
	float metallic;
	/** @brief Opaqueness, higher is more opaque */
	float transparency;
	Meta meta;
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Material, color, roughness, metallic, transparency, meta);
	/** @endcond */
};

/**
 * @brief Simple texture with UV coordinates
 */
class Texture
{ // TODO: not yet implemented in the python plugin
	public:
	Meta meta;
	/** @brief Texture file path relative to .jdscn file. Must be png */
	std::string path;
	/** @brief Mapping of 3D vertex coordinates to 2D coordinates on the texture image */
	UV uv;
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Texture, meta, path, uv);
	/** @endcond */
};

class Camera
{
	public:
	Position position;
	Orientation orientation;
	Meta meta;
	/**
	 * @brief Focal length of the lens in millimeters, as in Blender
	 * This property is converted to pixels
	 */
	float focalLength;
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Camera, position, orientation, meta, focalLength);
	/** @endcond */
};

class Light
{
	public:
	/** @brief Light type, can be point, environment, sun and spot */
	std::string type;
	Meta meta;
	Orientation orientation;
	Color color;
	Position position;
	/** @brief Power in watts */
	float power;
	/** @brief Light source radius, defines blurryness of shadow edges */
	float radius;
	/** @brief Cone radius, only applies to spot lights, and defines how large the spot's circle is */
	float cone;
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Light, type, meta, orientation, color, position, power, radius,
								   cone);
	/** @endcond */
};

/**
 * @brief 3D mesh
 */
class Object
{
	public:
	Orientation orientation;
	Position position;
	Scale scale;
	Vertices vertices;
	Meta meta;
	Material material;
	/**
	 * @brief Apply a transformation to all the vertices
	 *
	 * @param std::function(jdscn::Position) lambda function that returns a modified `jdscn::Position`
	 */
	void transform(std::function<jdscn::Position(jdscn::Position)>);
	/**
	 * @brief Transform the scale of an object
	 *
	 * @param jdscn::Scale x,y,z scale factor
	 * @param bool Adds the scale factor to the object's scale member if true
	 */
	void transformScale(jdscn::Scale, bool);
	/**
	 * @brief Transform the orientation of an object
	 *
	 * @param jdscn::Orientation x,y,z rotation
	 * @param bool Adds the roation to the object's orientation member if true
	 */
	void transformRotate(jdscn::Orientation, bool);
	/**
	 * @brief Transform the position of an object
	 *
	 * @param jdscn::Position x,y,z position shift
	 * @param bool Adds the position shift to the object's position member if true
	 */
	void transformTranslate(jdscn::Position, bool);
	/**
	 * @brief FIXME: DEV BRANCH MERGE
	 */
	UVFloat projectVertices(Camera);
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Object, orientation, position, scale, vertices, meta, material);
	/** @endcond */
	/* Texture texture; */
};

/**
 * @brief Meta for the `jdscn::Scene` class
 */
class SceneMeta
{
	public:
	/** @brief jdscn version */
	std::string version;
	/** @brief jdscn generator */
	std::string generator;
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneMeta, version, generator);
	/** @endcond */
};

class Scene
{
	public:
	SceneMeta meta;
	Camera camera;
	std::vector<Light> lights;
	std::vector<Object> objects;
	/**
	 * @brief Draw each object in the scene
	 *
	 * @param Win::Canvas canvas to draw the scene to
	 * @param int current frame
	 */
	void draw(Win::Canvas, int);
	/** @cond INTERNAL */
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Scene, meta, camera, lights, objects);
	/** @endcond */
};

}; // namespace jdscn
