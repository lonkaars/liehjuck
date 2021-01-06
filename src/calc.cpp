#include "calc.h"
#include "jdscn_types.h"
#include "win.h"
#include <array>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <utility>

namespace calc
{

jdscn::FloatXY rotate2D(jdscn::FloatXY point, float angle)
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);
	return jdscn::FloatXY({cos * point[0] - sin * point[1], sin * point[0] + cos * point[1]});
}

jdscn::Position rotate3D(jdscn::Position point, jdscn::Orientation rotation)
{
	jdscn::FloatXY rx = rotate2D({point[1], point[2]}, rotation[0]);
	point = {point[0], rx[0], rx[1]};
	jdscn::FloatXY ry = rotate2D({point[0], point[2]}, -rotation[1]);
	point = {ry[0], point[1], ry[1]};
	jdscn::FloatXY rz = rotate2D({point[0], point[1]}, rotation[2]);
	point = {rz[0], rz[1], point[2]};
	return point;
}

jdscn::FloatXYZ project(jdscn::Position a, jdscn::Camera camera)
{
	// https://en.wikipedia.org/wiki/3D_projection#Perspective_projection
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
	return {(e[2] / d[2]) * d[0] + e[0], (e[2] / d[2]) * d[1] + e[1], d[2]};
}

std::vector<jdscn::Position> interpolateBetweenPoints(jdscn::Position start, jdscn::Position end)
{
	std::vector<jdscn::Position> out;
	int step = start[1] > end[1] ? -1 : 1;
	int lineEnd = end[1] + step;
	float Xchange = float(end[0] - start[0]) / float(end[1] - start[1]);
	float Zchange = float(end[2] - start[2]) / float(end[1] - start[1]);
	for(int y = start[1]; y != lineEnd; y += step)
		out.push_back({ start[0] + (y - start[1]) * Xchange,
						start[1] + (y - start[1]),
						start[2] + (y - start[1]) * Zchange});
	return out;
}

std::vector<jdscn::Position> fillBetweenPoints(jdscn::Position start, jdscn::Position end)
{
	std::vector<jdscn::Position> out;
	int step = start[0] > end[0] ? -1 : 1;
	int lineEnd = end[0];
	float Zchange = float(end[2] - start[2]) / float(end[0] - start[0]);
	for(int x = start[0]; x != lineEnd; x += step)
	{
		out.push_back({float(x), start[1], start[2] + (x - start[0]) * Zchange});
	}

	return out;
}

void swap(jdscn::Tri &tri, int a, int b)
{
	jdscn::Position temp = tri[a];
	tri[a] = tri[b];
	tri[b] = temp;
}

jdscn::Tri sortTriangleY(jdscn::Tri tri) // Sorry for bad code, I don't really know if this would be better with some built-in sort
{
	int smallest = 0;
	for(int i = 1; i < tri.size(); i++)
		if(tri[i][1] < tri[smallest][1])
			smallest = i;
	swap(tri, 0, smallest);

	int biggest = 0;
	for(int i = 1; i < tri.size(); i++)
		if(tri[i][1] > tri[biggest][1])
			biggest = i;
	swap(tri, 2, biggest);

	return tri;
}

std::vector<jdscn::Position> filledTriangle(jdscn::Tri tri)
{
	tri = sortTriangleY(tri);
	std::vector<jdscn::Position> out;
		
	float slope01 = float(tri[0][0] - tri[1][0]) / float(tri[0][1] - tri[1][1]);
	float slope02 = float(tri[0][0] - tri[2][0]) / float(tri[0][1] - tri[2][1]);
	float slope12 = float(tri[1][0] - tri[2][0]) / float(tri[1][1] - tri[2][1]);
	float Zslope01 = float(tri[0][2] - tri[1][2]) / float(tri[0][1] - tri[1][1]);
	float Zslope02 = float(tri[0][2] - tri[2][2]) / float(tri[0][1] - tri[2][1]);
	float Zslope12 = float(tri[1][2] - tri[2][2]) / float(tri[1][1] - tri[2][1]);
	
	jdscn::Position point1 = tri[0];
	jdscn::Position point2 = tri[0];
	//std::cout << "New triangle: " << tri[0][0] << ", " << tri[0][1] << " and " << tri[1][0] << ", " << tri[1][1] << " and " << tri[2][0] << ", " << tri[2][1] << std::endl;
	for(int y = tri[0][1]; y < int(tri[1][1]); y++)
	{
		//std::cout << "between: " << point1[0] << ", " << point1[1] << " and " << point2[0] << ", " << point2[1] << std::endl;
		std::vector<jdscn::Position> widthline = fillBetweenPoints(point1, point2);
		out.insert(out.end(), widthline.begin(), widthline.end());
		point1 = {point1[0] + slope01, point1[1] + 1, point1[2] + Zslope01};
		point2 = {point2[0] + slope02, point2[1] + 1, point2[2] + Zslope02};
	}

	for(int y = tri[1][1]; y < int(tri[2][1]); y++)
	{
		//std::cout << "between: " << point1[0] << ", " << point1[1] << " and " << point2[0] << ", " << point2[1] << std::endl;
		std::vector<jdscn::Position> widthline = fillBetweenPoints(point1, point2);
		out.insert(out.end(), widthline.begin(), widthline.end());
		point1 = {point1[0] + slope12, point1[1] + 1, point1[2] + Zslope12};
		point2 = {point2[0] + slope02, point2[1] + 1, point2[2] + Zslope02};
	}

	return out;
}}; // namespace calc

