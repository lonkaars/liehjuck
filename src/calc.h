#pragma once
#include "jdscn_types.h"
#include "scene.h"
#include <array>
#include <vector>

/** @file calc.h */

/** @brief 2D and 3D calculations */
namespace calc
{

/**
 * @brief Rotate a 2D point around the origin (0, 0)
 *
 * @param jdscn::FloatXY Point to rotate
 * @param float Counterclockwise rotation in radians
 *
 * @return jdscn::FloatXY Rotated point
 */
jdscn::FloatXY rotate2D(jdscn::FloatXY, float);
/**
 * @brief Rotate a 3D point around the origin (0, 0, 0)
 *
 * @param jdscn::Position Point to rotate
 * @param jdscn::Orientation Euler rotation
 *
 * @return jdscn::Position Rotated point
 */
jdscn::Position rotate3D(jdscn::Position, jdscn::Orientation);
/**
 * @brief Project a 3D point to screen coordinates using a Camera
 *
 * @param jdscn::Position Point to project
 * @param jdscn::Camera Camera to project with
 *
 * @return jdscn::FloatXYZ (screen coordinate x, screen coordinate y, z depth after camera
 * transform)
 */
jdscn::FloatXYZ project(jdscn::Position, jdscn::Camera);
/**
 * @brief Gives coordinates originating from top-left corner of a window instead of originating from
 * the middle of the window
 *
 * @param jdscn::FloatXY Point originating from the middle
 * @param win::Canvas& Canvas that the point is on
 *
 * @return jdscn::FloatXY Pointcoordinates originating from top-left
 */
jdscn::FloatXY toCoordsFromTopLeft(jdscn::FloatXY, win::Canvas &);

/**
 * @brief Scanline interpolation between 2 points
 *
 * @param jdscn::Position2D start point
 * @param jdscn::Position2D end point
 *
 * @return std::vector<Position2D> with all the points in between start and end
 */
std::vector<jdscn::Position2D> interpolateBetweenPoints(jdscn::Position2D, jdscn::Position2D);

}; // namespace calc
