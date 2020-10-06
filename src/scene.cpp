#include "scene.h"
#include "utility.h"
#include <iostream>
#include <math.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

void jdscn::Scene::draw()
{
	for (jdscn::Object object : this->objects) {
		object.transformScale({5, 15, 3});
		std::cout << object.vertices[0][0][0] << std::endl;
		std::cout << object.vertices[0][0][1] << std::endl;
		std::cout << object.vertices[0][0][2] << std::endl;
		std::cout << object.scale[0] << std::endl;
		std::cout << object.scale[1] << std::endl;
		std::cout << object.scale[2] << std::endl;
	}
}

// FIXME: Alsmost duplicate functions
void jdscn::Object::transformScale(std::array<float, 3> scaleFactor)
{
	std::for_each(this->vertices.begin(), this->vertices.end(),
				  [&scaleFactor](std::array<jdscn::Position, 3> &vertex) {
					  std::for_each(vertex.begin(), vertex.end(),
									[&scaleFactor](jdscn::Position &pos) {
										for (int i = 0; i < pos.size(); i++)
											pos[i] *= scaleFactor[i];
									});
				  });
	for (int a = 0; a < this->scale.size(); a++)
		this->scale[a] += scaleFactor[a];
}

void jdscn::Object::transformPosition(std::array<float, 3> positionShift)
{
	std::for_each(this->vertices.begin(), this->vertices.end(),
				  [&positionShift](std::array<jdscn::Position, 3> &vertex) {
					  std::for_each(vertex.begin(), vertex.end(),
									[&positionShift](jdscn::Position &pos) {
										for (int i = 0; i < pos.size(); i++)
											pos[i] += positionShift[i];
									});
				  });
	for (int a = 0; a < this->scale.size(); a++)
		this->position[a] += positionShift[a];
}

void jdscn::Object::transformRotation(std::array<float, 3> rotation)
{
	std::for_each(
		this->vertices.begin(), this->vertices.end(),
		[&rotation](std::array<jdscn::Position, 3> &vertex) {
			std::for_each(vertex.begin(), vertex.end(), [&rotation](jdscn::Position &pos) {
				std::array<float, 2> rz = utility::rotate2D({pos[0], pos[1]}, rotation[2]);
				pos = {rz[0], rz[1], pos[2]};
				std::array<float, 2> ry = utility::rotate2D({pos[0], pos[2]}, rotation[1]);
				pos = {ry[0], pos[1], ry[1]};
				std::array<float, 2> rx = utility::rotate2D({pos[1], pos[2]}, rotation[0]);
				pos = {pos[0], rx[0], rx[1]};
			});
		});
	for (int a = 0; a < this->orientation.size(); a++)
		this->orientation[a] += rotation[a];
}

std::vector<std::array<jdscn::FloatXY, 3>> jdscn::Object::projectVertices(jdscn::Camera camera)
{
	std::vector<std::array<jdscn::FloatXY, 3>> projectedVertices;
	std::for_each(
		this->vertices.begin(), this->vertices.end(),
		[&camera, &projectedVertices](std::array<jdscn::Position, 3> &vertex) {
			std::array<jdscn::FloatXY, 3> outVert;
			for (int p = 0; p < vertex.size(); p++) {
				// https://en.wikipedia.org/wiki/3D_projection#Perspective_projection
				jdscn::Position a = vertex[p];			   // point
				jdscn::Position c0 = camera.position;	   // camera pos
				jdscn::Position e = {0, 0, -200};		   // display surface
				jdscn::Orientation o = camera.orientation; // camera rotation

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
