#pragma once
#include "jdscn_types.h"
#include "scene.h"
#include <array>
#include <vector>

namespace calc
{

jdscn::FloatXY rotate2D(jdscn::FloatXY, float);
jdscn::Position rotate3D(jdscn::Position, jdscn::Orientation);
jdscn::FloatXYZ project(jdscn::Position, jdscn::Camera);

}; // namespace calc
