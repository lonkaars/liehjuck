#include "scene.h"
#include <math.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace jdscn {

/* void from_json(const nlohmann::json& j, FloatXYZ& f) { */
/* 	j.at(0).get_to(f.x); */
/* 	j.at(1).get_to(f.y); */
/* 	j.at(2).get_to(f.z); */
/* }; */

/* void from_json(const nlohmann::json& j, Position2D& p) { */
/* 	j.at(0).get_to(p.x); */
/* 	j.at(1).get_to(p.y); */
/* }; */

/* void from_json(const nlohmann::json& j, Color& c) { */
/* 	j.at(0).get_to(c.r); */
/* 	j.at(1).get_to(c.g); */
/* 	j.at(2).get_to(c.b); */
/* }; */

/* NLOHMANN_DEFINE_TYPE_INTRUSIVE(Material, color, roughness, metallic, transparency, meta); */
/* NLOHMANN_DEFINE_TYPE_INTRUSIVE(Texture, meta, path, uv); */
/* NLOHMANN_DEFINE_TYPE_INTRUSIVE(Camera, position, orientation, meta, focalLength); */
/* NLOHMANN_DEFINE_TYPE_INTRUSIVE(Light, type, meta, orientation, color, position, power, radius, cone); */
/* NLOHMANN_DEFINE_TYPE_INTRUSIVE(Scene, meta, camera, lights, objects); */

/* void from_json(const nlohmann::json& j, Object& o) { */
/* 	j.at("orientation").get_to(o.orientation); */
/* 	j.at("position").get_to(o.position); */
/* 	j.at("scale").get_to(o.scale); */
/* 	o.vertices = { */
/* 		{ */
/* 			{0, 1, 0}, */
/* 			{0, 1, 0}, */
/* 			{0, 1, 0} */
/* 		} */
/* 	}; */
/* 	/1* for(json vert : j.at("vertices")) { *1/ */
/* 	/1* 	Position vertex[3] { *1/ */
/* 	/1* 		vert[0].get<Position>(), *1/ */
/* 	/1* 		vert[1].get<Position>(), *1/ */
/* 	/1* 		vert[2].get<Position>() *1/ */
/* 	/1* 	}; *1/ */
/* 	/1* 	o.vertices.push_back(vertex); *1/ */
/* 	/1* } *1/ */
/* 	j.at("meta").get_to(o.meta); */
/* 	j.at("material").get_to(o.material); */
/* 	j.at("texture").get_to(o.texture); */
/* }; */

}

