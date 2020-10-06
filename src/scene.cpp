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
		// object.project()
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
