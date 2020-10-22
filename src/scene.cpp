#include "scene.h"
#include "../lib/gfx/gfx.h"
#include "utility.h"
#include "win.h"
#include <iostream>
#include <math.h>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <vector>

float rotation = 0;

void jdscn::Object::transform(std::function<jdscn::Position(jdscn::Position)> operation)
{
	std::for_each(this->vertices.begin(), this->vertices.end(), [&operation](jdscn::Tri &tri) {
		std::for_each(tri.begin(), tri.end(),
					  [&operation](jdscn::Position &pos) { pos = operation(pos); });
	});
}

void jdscn::Scene::draw(Win::Canvas canvas, int frame = 0)
{
	for (jdscn::Object object : this->objects) {
		object.orientation[0] = object.orientation[0] + rotation;
		object.transformScale(object.scale, false);
		object.transformRotate(object.orientation, true);
		object.transformTranslate(object.position, false);
		jdscn::UVFloat projection = object.projectVertices(this->camera);
		for (jdscn::TriXY tri : projection)
			for (jdscn::FloatXY pos : tri)
			{				
				canvas.draw(canvas.width/2 - pos[0], canvas.height/2 + pos[1], object.material.color);
			}
		rotation = rotation + 0.1;
	}
	canvas.flush();
	canvas.clear();
}

void jdscn::Object::transformScale(jdscn::Scale scaleFactor, bool apply = true)
{
	this->transform([&scaleFactor](jdscn::Position pos) {
		for (int i = 0; i < pos.size(); i++)
			pos[i] *= scaleFactor[i];
		return pos;
	});
	if (apply)
		for (int a = 0; a < this->scale.size(); a++)
			this->scale[a] += scaleFactor[a];
}

void jdscn::Object::transformTranslate(jdscn::Position positionShift, bool apply = true)
{
	this->transform([&positionShift](jdscn::Position pos) {
		for (int i = 0; i < pos.size(); i++)
			pos[i] += positionShift[i];
		return pos;
	});
	if (apply)
		for (int a = 0; a < this->scale.size(); a++)
			this->position[a] += positionShift[a];
}

void jdscn::Object::transformRotate(jdscn::Orientation rotation, bool apply = true)
{
	this->transform([&rotation](jdscn::Position pos) {
		jdscn::FloatXY rx = utility::rotate2D({pos[1], pos[2]}, rotation[0]);
		pos = {pos[0], rx[0], rx[1]};
		jdscn::FloatXY ry = utility::rotate2D({pos[0], pos[2]}, -rotation[1]);
		pos = {ry[0], pos[1], ry[1]};
		jdscn::FloatXY rz = utility::rotate2D({pos[0], pos[1]}, rotation[2]);
		pos = {rz[0], rz[1], pos[2]};
		return pos;
	});
	if (apply)
		for (int a = 0; a < this->orientation.size(); a++)
			this->orientation[a] += rotation[a];
}

jdscn::UVFloat jdscn::Object::projectVertices(jdscn::Camera camera)
{
	jdscn::UVFloat projectedVertices;
	std::for_each(
		this->vertices.begin(), this->vertices.end(),
		[&camera, &projectedVertices](jdscn::Tri &tri) {
			std::array<jdscn::FloatXY, 3> outVert;
			for (int p = 0; p < tri.size(); p++) {
				// https://en.wikipedia.org/wiki/3D_projection#Perspective_projection
				jdscn::Position a = tri[p];									  // point
				jdscn::Position c0 = camera.position;						  // camera pos
				jdscn::Position e = {0, 0, camera.focalLength * float(35.6)}; // display surface
				jdscn::Orientation o = camera.orientation;					  // camera rotation

				// wikipedia abbreviations
				float x = a[0] - c0[0];
				float y = a[1] - c0[1];
				float z = a[2] - c0[2];
				jdscn::Position s = {std::sin(o[0]), std::sin(o[1]), std::sin(o[2])};
				jdscn::Position c = {std::cos(o[0]), std::cos(o[1]), std::cos(o[2])};

				// camera transform
				jdscn::Position d = {
					c[1] * (s[2] * y + c[2] * x) - s[1] * z,
					s[0] * (c[1] * z + s[1] * (s[2] * y + c[2] * x)) + c[0] * (c[2] * y - s[2] * x),
					c[0] * (c[1] * z + s[1] * (s[2] * y + c[2] * x)) - s[0] * (c[2] * y - s[2] * x),
				};

				// screen coordinates
				outVert[p] = {(e[2] / d[2]) * d[0] + e[0], (e[2] / d[2]) * d[1] + e[1]};
			}
			projectedVertices.push_back(outVert);
		});
	return projectedVertices;
}
