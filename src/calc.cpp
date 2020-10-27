#include "calc.h"
#include "jdscn_types.h"
#include "win.h"
#include <array>
#include <math.h>
#include <stdlib.h>
#include <iostream>
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

jdscn::FloatXY recalculateCoords(jdscn::FloatXY point, win::Canvas& c)
{
	point[0] = c.width / 2 + point[0];
	point[1] = c.height / 2 - point[1];
	return point;
}

void drawLine(jdscn::FloatXY start, jdscn::FloatXY end, jdscn::Color c, win::Canvas& canvas)
{
	start = recalculateCoords(start, canvas);
	end = recalculateCoords(end, canvas);
	
	if(start[1] > end[1])
	{
		std::swap(start[0], end[0]);
		std::swap(start[1], end[1]);
	}

	float changePerPixel = (end[0] - start[0]) / (end[1] - start[1]);
	for(int y = 0; y < (end[1] - start[1]); y++)
	{
		canvas.draw(start[0] + y * changePerPixel, start[1] + y, c);
	}
}

void drawTriangle(jdscn::FloatXY point1, jdscn::FloatXY point2, jdscn::FloatXY point3, jdscn::Color c, win::Canvas& canvas)
{
	drawLine(point1, point2, c, canvas);
	drawLine(point2, point3, c, canvas);
	drawLine(point3, point1, c, canvas);
}

}; // namespace calc
