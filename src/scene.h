#pragma once
#include <math.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace jdscn
{

/* class FloatXYZ { */
/* 	public: */
/* 	float x; */
/* 	float y; */
/* 	float z; */
/* }; */
/* void from_json(const nlohmann::json&, FloatXYZ&); */

/* using Position = FloatXYZ; */
/* using Scale = FloatXYZ; */
/* using Orientation = FloatXYZ; */

/* class Position2D */
/* { */
/* 	public: */
/* 	int x; */
/* 	int y; */
/* }; */
/* void from_json(const nlohmann::json&, Position2D&); */

/* class Color */
/* { */
/* 	public: */
/* 	int r; */
/* 	int g; */
/* 	int b; */
/* 	// int [0 -> 255] */
/* }; */
/* void from_json(const nlohmann::json&, Color&); */

/* class Meta */
/* { */
/* 	public: */
/* 	std::string name; */
/* 	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Meta, name); */
/* }; */

/* class Material */
/* { */
/* 	public: */
/* 	Color color; */
/* 	float roughness; */
/* 	float metallic; */
/* 	float transparency; */
/* 	Meta meta; */
/* }; */

/* class UV */
/* { */
/* 	public: */
/* 	std::vector<Position2D[3]> uv; */
/* }; */
/* void from_json(const nlohmann::json&, UV&); */

/* class Texture */
/* { // TODO: not yet implemented in the python plugin */
/* 	public: */
/* 	Meta meta; */
/* 	std::string path; */
/* 	UV uv; */
/* }; */

/* class Camera */
/* { */
/* 	public: */
/* 	Position position; */
/* 	Orientation orientation; */
/* 	Meta meta; */
/* 	float focalLength; */
/* }; */

/* class Light */
/* { */
/* 	public: */
/* 	std::string type; */
/* 	Meta meta; */
/* 	Orientation orientation; */
/* 	Color color; */
/* 	Position position; */
/* 	float power; */
/* 	float radius; */
/* 	float cone; */
/* }; */

/* class Object */
/* { */
/* 	public: */
/* 	Orientation orientation; */
/* 	Position position; */
/* 	Scale scale; */
/* 	std::vector<Position[3]> vertices; */
/* 	Meta meta; */
/* 	Material material; */
/* 	Texture texture; */
/* }; */
/* void from_json(const nlohmann::json&, Object&); */

class SceneMeta
{
	public:
	std::string version;
	std::string generator;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneMeta, version, generator);
};

/* class Scene */
/* { */
/* 	public: */
/* 	SceneMeta meta; */
/* 	Camera camera; */
/* 	std::vector<Light> lights; */
/* 	std::vector<Object> objects; */
/* }; */

}; // namespace jdscn
