#include "scene.h"
#include <math.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace jdscn {

void from_json(const nlohmann::json& j, FloatXYZ& f) {
	j.at(0).get_to(f.x);
	j.at(1).get_to(f.y);
	j.at(2).get_to(f.z);
};

void from_json(const nlohmann::json& j, Position2D& p) {
	j.at(0).get_to(p.x);
	j.at(1).get_to(p.y);
};

void from_json(const nlohmann::json& j, Color& c) {
	j.at(0).get_to(c.r);
	j.at(1).get_to(c.g);
	j.at(2).get_to(c.b);
};

void from_json(const nlohmann::json& j, Meta& m) {
	j.at("name").get_to(m.name);
};

void from_json(const nlohmann::json& j, Material& m) {
	j.at("color").get_to(m.color);
	j.at("roughness").get_to(m.roughness);
	j.at("metallic").get_to(m.metallic);
	j.at("transparency").get_to(m.transparency);
	j.at("meta").get_to(m.meta);
};

void from_json(const nlohmann::json& j, Texture& t) {
	j.at("meta").get_to(t.meta);
	j.at("path").get_to(t.path);
	j.at("uv").get_to(t.uv);
};

void from_json(const nlohmann::json& j, Camera& c) {
	j.at("position").get_to(c.position);
	j.at("orientation").get_to(c.orientation);
	j.at("meta").get_to(c.meta);
	j.at("focalLength").get_to(c.focalLength);
};

void from_json(const nlohmann::json& j, Light& l) {
	j.at("type").get_to(l.type);
	j.at("meta").get_to(l.meta);
	j.at("orientation").get_to(l.orientation);
	j.at("color").get_to(l.color);
	j.at("position").get_to(l.position);
	j.at("power").get_to(l.power);
	j.at("radius").get_to(l.radius);
	j.at("cone").get_to(l.cone);
};

void from_json(const nlohmann::json& j, Object& o) {
	j.at("orientation").get_to(o.orientation);
	j.at("position").get_to(o.position);
	j.at("scale").get_to(o.scale);
	o.vertices = {
		{
			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0}
		}
	};
	/* for(json vert : j.at("vertices")) { */
	/* 	Position vertex[3] { */
	/* 		vert[0].get<Position>(), */
	/* 		vert[1].get<Position>(), */
	/* 		vert[2].get<Position>() */
	/* 	}; */
	/* 	o.vertices.push_back(vertex); */
	/* } */
	j.at("meta").get_to(o.meta);
	j.at("material").get_to(o.material);
	j.at("texture").get_to(o.texture);
};

void from_json(const nlohmann::json& j, SceneMeta& m) {
	j.at("version").get_to(m.version);
	j.at("generator").get_to(m.generator);
};

void from_json(const nlohmann::json& j, Scene& s) {
	j.at("meta").get_to(s.meta);
	j.at("camera").get_to(s.camera);
	j.at("lights").get_to(s.lights);
	j.at("objects").get_to(s.objects);
};

}

