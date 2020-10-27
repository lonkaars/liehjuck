#include "scene.h"
#include "calc.h"
#include "win.h"
#include <iostream>
#include <math.h>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <vector>

void jdscn::Scene::draw(win::Canvas canvas, int frame = 0)
{
	for (jdscn::Object object : this->objects) {
		object.transformScale(object.scale, false);
		object.transformRotate(object.orientation, false);
		object.transformTranslate(object.position, false);
		jdscn::Vertices projection = object.projectVertices(this->camera);
		for (jdscn::Tri tri : projection)
			for (jdscn::FloatXYZ pos : tri)
				if (pos[2] < -0.02) // Near clipping
					canvas.draw(-pos[0], -pos[1], object.material.color);
	}
	canvas.flush();
	canvas.clear();
}

void jdscn::Object::transform(std::function<jdscn::Position(jdscn::Position)> operation)
{
	std::for_each(this->vertices.begin(), this->vertices.end(), [&operation](jdscn::Tri &tri) {
		std::for_each(tri.begin(), tri.end(),
					  [&operation](jdscn::Position &pos) { pos = operation(pos); });
	});
}

void jdscn::Object::transformScale(jdscn::Scale scaleFactor) {
	jdscn::Object::transformScale(scaleFactor, true);
}
void jdscn::Object::transformScale(jdscn::Scale scaleFactor, bool apply)
{
	this->transform([&scaleFactor](jdscn::Position pos) {
		for (int i = 0; i < pos.size(); i++)
			pos[i] *= scaleFactor[i];
		return pos;
	});
	for (int a = 0; a < this->scale.size(); a++)
		this->scale[a] += scaleFactor[a] * int(apply);
}

void jdscn::Object::transformTranslate(jdscn::Position positionShift) {
	jdscn::Object::transformTranslate(positionShift, true);
}
void jdscn::Object::transformTranslate(jdscn::Position positionShift, bool apply)
{
	this->transform([&positionShift](jdscn::Position pos) {
		for (int i = 0; i < pos.size(); i++)
			pos[i] += positionShift[i];
		return pos;
	});
	for (int a = 0; a < this->scale.size(); a++)
		this->position[a] += positionShift[a] * int(apply);
}

void jdscn::Object::transformRotate(jdscn::Orientation rotation) {
	jdscn::Object::transformRotate(rotation, true);
}
void jdscn::Object::transformRotate(jdscn::Orientation rotation, bool apply)
{
	this->transform([&rotation](jdscn::Position pos) { return calc::rotate3D(pos, rotation); });
	for (int a = 0; a < this->orientation.size(); a++)
		this->orientation[a] += rotation[a] * int(apply);
}

jdscn::Vertices jdscn::Object::projectVertices(jdscn::Camera camera)
{
	jdscn::Vertices out;
	std::for_each(this->vertices.begin(), this->vertices.end(), [&camera, &out](jdscn::Tri tri) {
		jdscn::Tri out_tri;
		for (int i = 0; i < tri.size(); i++)
			out_tri[i] = calc::project(tri[i], camera);
		out.push_back(out_tri);
	});
	return out;
}
